// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTInvaderManager.generated.h"

class USoundCue;
class AGFTInvader;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStageClear);

USTRUCT()
struct FInvaderConfiguration
{
	GENERATED_BODY()

	float MovementRate = 1.f;
	float FinalMovementRate = 0.1f;
	float MinAttackInterval = 1.f;
	float MaxAttackInterval = 1.f;

	UPROPERTY()
	TArray<TObjectPtr<USoundBase>> MoveSounds;
};

/*
 * This class will manage all invaders in the level. It will move them and tell them when to shoot.
 * It should be spawned and initialized by the GameMode, which is why configuration will happen in a GameMode blueprint.
 * All it does could be implemented directly in the GameMode, but like this it's more obvious what it does.
 */
UCLASS(NotBlueprintable)
class GFT_SPRING23_API AGFTInvaderManager : public AActor
{
	GENERATED_BODY()

public:
	AGFTInvaderManager();

	// Set some values from outside and start timer
	void Initialize(FInvaderConfiguration InvaderConfig);

	// Will fire once all Invaders have been destroyed
	UPROPERTY()
	FOnStageClear OnStageClear;

private:
	// Callback whenever an invader overlaps something
	UFUNCTION()
	void OnInvaderBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Callback whenever an invader ends overlapping something
	UFUNCTION()
	void OnInvaderEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Callback whenever an invader is removed from the level
	UFUNCTION()
	void OnInvaderEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	// Callback for MovementTimer
	UFUNCTION()
	void PerformMove();

	// Callback for AttackTimer
	void PerformAttack();

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
	TArray<TObjectPtr<USoundBase>> MoveSounds;
	UPROPERTY(VisibleInstanceOnly)
	int32 MoveSoundIndex = 0;
	UPROPERTY(VisibleInstanceOnly)
	bool bWasReverted = false;
	UPROPERTY(VisibleInstanceOnly)
	bool bShouldMoveDown = true;

	// Internal values used for attack calculations
	UPROPERTY(VisibleInstanceOnly)
	float MinAttackInterval = 1.f;
	UPROPERTY(VisibleInstanceOnly)
	float MaxAttackInterval = 1.f;

	// Timer to handle repeated movement
	FTimerHandle MovementTimer;

	// Timer to handle repeated attacks
	FTimerHandle AttackTimer;
};