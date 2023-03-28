// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameMode.h"

#include "GFT_Spring23/Actors/GFTBall.h"

void AGFTGameMode::SpawnBall(const FTransform& WorldTransform) const
{
	if (BallClass == nullptr)
	{
		UE_LOG(LogGameMode, Warning, TEXT("There is no Ball Class set in the GameMode, please check."));
		return;
	}

	GetWorld()->SpawnActor<AGFTBall>(BallClass, WorldTransform);
}