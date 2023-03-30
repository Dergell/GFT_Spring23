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
	// Will spawn a new ball on the paddle
	void SpawnBall(const FTransform& WorldTransform);

protected:
	virtual void BeginPlay() override;

	// Callback when an actor leaves the GameSpace trigger volume
	UFUNCTION()
	void OnActorLeavingGameSpace(AActor* OverlappedActor, AActor* OtherActor);

	// Blueprint class to use when spawning a Ball
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT)
	TSubclassOf<AGFTBall> BallClass;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 ActiveBalls = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 MaxBalls = 1;
};