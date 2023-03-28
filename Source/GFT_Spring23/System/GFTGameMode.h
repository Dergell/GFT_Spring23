// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GFTGameMode.generated.h"

class AGFTBall;

UCLASS()
class GFT_SPRING23_API AGFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void SpawnBall(const FTransform& WorldTransform) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT)
	TSubclassOf<AGFTBall> BallClass;
};