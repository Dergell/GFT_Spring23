// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GFTGameMode.generated.h"

class AGFTInvaderManager;
class AGFTBall;

UCLASS()
class GFT_SPRING23_API AGFTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Will spawn a new ball on the paddle
	void SpawnBall(const FTransform& WorldTransform);

protected:
	virtual void BeginPlay() override;

	// Callback when the player lost all lives
	UFUNCTION()
	void GameOver();

	// Callback when an actor leaves the GameSpace trigger volume
	UFUNCTION()
	void OnActorLeavingGameSpace(AActor* OverlappedActor, AActor* OtherActor);

	// Blueprint class to use when spawning a Ball
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GFT|Ball Configuration")
	TSubclassOf<AGFTBall> BallClass;

private:
	// Keeps track of currently active balls
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="GFT|Ball Configuration", meta=(AllowPrivateAccess = "true"))
	int32 ActiveBalls = 0;

	// Max number of balls active at the same time
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GFT|Ball Configuration", meta=(AllowPrivateAccess = "true"))
	int32 MaxBalls = 1;

	// The rate in seconds when movement should be performed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|Invader Movement", meta=(AllowPrivateAccess = "true"))
	float MovementRate = 1.f;

	// The final movement rate at which the last remaining invader will move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|Invader Movement", meta=(AllowPrivateAccess = "true"))
	float FinalMovementRate = 0.1f;

	TObjectPtr<AGFTInvaderManager> InvaderManager;
};