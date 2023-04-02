// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTInvaderManager.generated.h"

class AGFTInvader;

/*
 * This class will manage movement for all invaders in the level
 */
UCLASS(NotBlueprintable)
class GFT_SPRING23_API AGFTInvaderManager : public AActor
{
	GENERATED_BODY()

public:
	AGFTInvaderManager();

protected:
	virtual void BeginPlay() override;

public:
	// Set some values from outside and start timer
	void Initialize(float InMovementRate, float InFinalMovementRate);

private:
	// Callback whenever an invader overlaps something
	UFUNCTION()
	void OnInvaderBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Callback whenever an invader ends overlapping something
	UFUNCTION()
	void OnInvaderEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Callback whenever an invader was destroyed
	UFUNCTION()
	void OnInvaderDestroyed(AActor* DestroyedActor);

	// Callback for MovementTimer
	UFUNCTION()
	void PerformMove();

	// Keep a list of all invaders in the level
	TArray<AGFTInvader*> InvaderList;

	// Internal values used for movement calculations
	UPROPERTY(VisibleInstanceOnly)
	float MovementRate = 1.f;
	UPROPERTY(VisibleInstanceOnly)
	float FinalMovementRate = 0.1f;
	UPROPERTY(VisibleInstanceOnly)
	FVector MovementVector;
	UPROPERTY(VisibleInstanceOnly)
	bool bWasReverted = false;
	UPROPERTY(VisibleInstanceOnly)
	bool bShouldMoveDown = true;

	// Timer to handle repeated movement
	FTimerHandle MovementTimer;
};