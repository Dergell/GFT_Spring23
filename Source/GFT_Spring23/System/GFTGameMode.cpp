// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameMode.h"

#include "GFTGameInstance.h"
#include "GFTPlayerController.h"
#include "GFT_Spring23/Actors/GFTBall.h"
#include "GFT_Spring23/Interfaces/GFTGameFramework.h"
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

void AGFTGameMode::SpawnBall(const FTransform& WorldTransform)
{
	if (BallClass == nullptr)
	{
		UE_LOG(LogGameMode, Warning, TEXT("There is no Ball Class set in the GameMode, please check."));
		return;
	}

	if (ActiveBalls >= MaxBalls)
	{
		UE_LOG(LogGameMode, Display, TEXT("Cannot spawn a new ball because MaxBalls is already reached."));
		return;
	}

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		World->SpawnActor<AGFTBall>(BallClass, WorldTransform);
		ActiveBalls++;
	}
}

void AGFTGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> GameSpaces;
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("GameSpace"), GameSpaces);
	for (AActor* GameSpace : GameSpaces)
	{
		GameSpace->OnActorEndOverlap.AddDynamic(this, &AGFTGameMode::OnActorLeavingGameSpace);
	}
}

void AGFTGameMode::GameOver()
{
	GetGameInstance<UGFTGameInstance>()->LoadMenuLevel();
}

void AGFTGameMode::OnActorLeavingGameSpace(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA(AGFTBall::StaticClass()))
	{
		AController* Controller = UGameplayStatics::GetPlayerController(this, 0);
		if (Controller != nullptr && Controller->Implements<UGFTGameFramework>())
		{
			IGFTGameFramework::Execute_BallLost(Controller);
		}

		ActiveBalls--;
	}

	OtherActor->Destroy();
}