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

	// Getter
	TSubclassOf<AGFTBall> GetBallClass() const;

	// Returns true if ActiveBalls is smaller than MaxBalls
	bool IsBallReady();

	// Adds one to ActiveBalls
	void AddActiveBall();

	// Removes one from ActiveBalls
	void RemoveActiveBall();

protected:
	virtual void BeginPlay() override;

	// Callback when the player lost all lives
	UFUNCTION()
	void GameOver();

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

	// The minimum time in seconds that need to pass between attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|Attack Configuration", meta=(AllowPrivateAccess = "true"))
	float MinAttackInterval = 1.f;

	// The maximum time in seconds until the next attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|Attack Configuration", meta=(AllowPrivateAccess = "true"))
	float MaxAttackInterval = 1.f;

	TObjectPtr<AGFTInvaderManager> InvaderManager;
};