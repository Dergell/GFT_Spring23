// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GFTInvaderMovement.generated.h"


UCLASS(ClassGroup=(GFT), meta=(BlueprintSpawnableComponent))
class GFT_SPRING23_API UGFTInvaderMovement : public UActorComponent
{
	GENERATED_BODY()

public:
	UGFTInvaderMovement();

protected:
	virtual void BeginPlay() override;

public:
	// Flips the MovementVector and may add downward movement (depending on bShouldMoveDown)
	void RevertMovementVector();

	// Reduce the MovementRate by MovementDecreaseRate
	void DecreaseMovementRate();

	// Setter
	void SetShouldMoveDown(bool bInShouldMoveDown);

private:
	// Callback used for MovementTimer
	UFUNCTION()
	void PerformMove();

	// The rate in seconds when movement should be performed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|InvaderMovement", meta=(AllowPrivateAccess = "true"))
	float MovementRate = 5.f;

	// The rate in seconds when movement should be performed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|InvaderMovement", meta=(AllowPrivateAccess = "true"))
	float MovementDecreaseRate = 0.1f;

	// The vector where the next movement will end
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|InvaderMovement", meta=(AllowPrivateAccess = "true"))
	FVector MovementVector = FVector(0.f, 0.f, 0.f);

	// When true, will add downward movement whenever RevertMovementVector is called
	bool bShouldMoveDown = true;

	// Keeps track if we already reverted this movement cycle
	bool bWasReverted = false;

	FTimerHandle MovementTimer;
};