// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameMode.h"

#include "GFTGameInstance.h"
#include "GFTPlayerController.h"
#include "GFT_Spring23/Actors/GFTBall.h"
#include "GFT_Spring23/Actors/GFTInvaderManager.h"

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

	InvaderManager = GetWorld()->SpawnActor<AGFTInvaderManager>(AGFTInvaderManager::StaticClass());

	FInvaderConfiguration InvaderConfig;
	InvaderConfig.MovementRate = MovementRate;
	InvaderConfig.FinalMovementRate = FinalMovementRate;
	InvaderConfig.MinAttackInterval = MinAttackInterval;
	InvaderConfig.MaxAttackInterval = MaxAttackInterval;
	InvaderManager->Initialize(InvaderConfig);
}

void AGFTGameMode::GameOver()
{
	GetGameInstance<UGFTGameInstance>()->LoadMenuLevel();
}