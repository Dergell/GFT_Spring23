// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameMode.h"

#include "GFTGameInstance.h"
#include "GFTPlayerController.h"
#include "GFTPlayerState.h"
#include "GFT_Spring23/Actors/GFTBall.h"
#include "GFT_Spring23/Actors/GFTBunker.h"
#include "GFT_Spring23/Actors/GFTInvader.h"
#include "GFT_Spring23/Actors/GFTInvaderManager.h"
#include "GFT_Spring23/Actors/GFTMothership.h"
#include "Kismet/GameplayStatics.h"

void AGFTGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AGFTPlayerController* Player = Cast<AGFTPlayerController>(NewPlayer);
	if (Player != nullptr)
	{
		Player->OnGameOver.AddDynamic(this, &AGFTGameMode::GameOver);
		Player->OnLiveLost.AddDynamic(this, &AGFTGameMode::OnLiveLost);
	}
}

bool AGFTGameMode::IsBallReady()
{
	if (ActiveBalls >= MaxBalls)
	{
		UE_LOG(LogGameMode, Display, TEXT("Cannot spawn a new ball because MaxBalls is already reached."));
		return false;
	}

	return true;
}

void AGFTGameMode::AddActiveBall()
{
	ActiveBalls++;
}

void AGFTGameMode::RemoveActiveBall()
{
	ActiveBalls--;
}

TSubclassOf<AGFTBall> AGFTGameMode::GetBallClass() const
{
	if (BallClass == nullptr)
	{
		UE_LOG(LogGameMode, Warning, TEXT("There is no Ball Class set in the GameMode, please check."));
		return nullptr;
	}

	return BallClass;
}

void AGFTGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->OnWorldBeginPlay.AddUObject(this, &AGFTGameMode::WorldBeginPlay);

	InvaderManager = GetWorld()->SpawnActor<AGFTInvaderManager>(AGFTInvaderManager::StaticClass());
	InvaderManager->OnStageClear.AddDynamic(this, &AGFTGameMode::StageClear);
}

/**
 * OnWorldBeginPlay triggers after all other BeginPlay methods. We need to do this here,
 * because in SetupInvaders we initialize the InvaderManager, which will move actors and depends
 * on the overlap triggers that don't trigger during normal BeginPlay. 
 */
void AGFTGameMode::WorldBeginPlay()
{
	SetupInvaders();

	TArray<AActor*> Invaders;
	UGameplayStatics::GetAllActorsOfClass(this, AGFTInvader::StaticClass(), Invaders);
	for (AActor* Invader : Invaders)
	{
		InvaderCache.Add(Invader->GetClass(), Invader->GetActorLocation());
	}
}

void AGFTGameMode::OnLiveLost()
{
	CleanupBalls();
}

void AGFTGameMode::GameOver(AGFTPlayerState* PlayerState)
{
	UGFTGameInstance* Instance = GetGameInstance<UGFTGameInstance>();
	if (Instance == nullptr)
	{
		return;
	}

	if (PlayerState != nullptr)
	{
		Instance->UpdateHighscore(PlayerState->GetScore());
	}

	Instance->LoadMenuLevel();
}

void AGFTGameMode::StageClear()
{
	UGFTGameInstance* Instance = GetGameInstance<UGFTGameInstance>();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->AdvanceStage();
	CleanupBalls();

	// At this point, this last invader is ending play, but it still in the level. He will be found in SetupInvaders,
	// which will result in an invalid pointer in InvaderList. To prevent this, we wait with the setup for the next tick. 
	GetWorldTimerManager().SetTimerForNextTick(this, &AGFTGameMode::SetupInvaders);
}

void AGFTGameMode::SetupInvaders()
{
	// Spawn the cached invaders. Will be empty on first run.
	for (auto Invader : InvaderCache)
	{
		GetWorld()->SpawnActor<AGFTInvader>(Invader.Key, Invader.Value, FRotator::ZeroRotator);
	}

	// Reset the size of all bunkers
	TArray<AActor*> Bunkers;
	UGameplayStatics::GetAllActorsOfClass(this, AGFTBunker::StaticClass(), Bunkers);
	for (AActor* Bunker : Bunkers)
	{
		Bunker->SetActorScale3D(FVector::OneVector);
	}

	// Initialize the InvaderManager
	FInvaderConfiguration InvaderConfig;
	InvaderConfig.MovementRate = MovementRate;
	InvaderConfig.FinalMovementRate = FinalMovementRate;
	InvaderConfig.MinAttackInterval = MinAttackInterval;
	InvaderConfig.MaxAttackInterval = MaxAttackInterval;
	InvaderConfig.MoveSounds = MoveSounds;
	InvaderManager->Initialize(InvaderConfig);

	// Set new timer for mothership
	const float Interval = FMath::FRandRange(MinMothershipInterval, MaxMothershipInterval);
	GetWorldTimerManager().SetTimer(MothershipTimer, this, &AGFTGameMode::SpawnMothership, Interval);
}

void AGFTGameMode::SpawnMothership()
{
	if (MothershipClass == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("MothershipClass in GameMode not set, cannot spawn mothership."));
		return;
	}

	// Find the spawn point marked by an empty actor
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("MothershipSpawn"), Actors);
	if (Actors.IsEmpty())
	{
		UE_LOG(LogClass, Warning, TEXT("Could not find actor with tag 'MothershipSpawn', cannot spawn mothership."));
		return;
	}

	// Spawn the mothership
	GetWorld()->SpawnActor<AGFTMothership>(MothershipClass, Actors.Top()->GetActorLocation(), FRotator::ZeroRotator);

	// Set a new timer for the next mothership
	const float Interval = FMath::FRandRange(MinMothershipInterval, MaxMothershipInterval);
	GetWorldTimerManager().SetTimer(MothershipTimer, this, &AGFTGameMode::SpawnMothership, Interval);
}

void AGFTGameMode::CleanupBalls()
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, AGFTBall::StaticClass(), Balls);
	for (AActor* Ball : Balls)
	{
		Ball->Destroy();
	}
}