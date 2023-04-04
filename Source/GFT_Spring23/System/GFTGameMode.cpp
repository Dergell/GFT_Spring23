// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameMode.h"

#include "GFTGameInstance.h"
#include "GFTPlayerController.h"
#include "GFT_Spring23/Actors/GFTBall.h"
#include "GFT_Spring23/Actors/GFTInvader.h"
#include "GFT_Spring23/Actors/GFTInvaderManager.h"
#include "Kismet/GameplayStatics.h"

void AGFTGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AGFTPlayerController* Player = Cast<AGFTPlayerController>(NewPlayer);
	if (Player != nullptr)
	{
		Player->OnGameOver.AddDynamic(this, &AGFTGameMode::GameOver);
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

void AGFTGameMode::GameOver()
{
	GetGameInstance<UGFTGameInstance>()->LoadMenuLevel();
}

void AGFTGameMode::StageClear()
{
	GetGameInstance<UGFTGameInstance>()->AdvanceStage();
	SetupInvaders();
}

void AGFTGameMode::SetupInvaders()
{
	// Spawn the cached invaders. Will be empty on first run.
	for (auto Invader : InvaderCache)
	{
		GetWorld()->SpawnActor<AGFTInvader>(Invader.Key, Invader.Value, FRotator::ZeroRotator);
	}

	// Initialize the InvaderManager
	FInvaderConfiguration InvaderConfig;
	InvaderConfig.MovementRate = MovementRate;
	InvaderConfig.FinalMovementRate = FinalMovementRate;
	InvaderConfig.MinAttackInterval = MinAttackInterval;
	InvaderConfig.MaxAttackInterval = MaxAttackInterval;
	InvaderManager->Initialize(InvaderConfig);
}