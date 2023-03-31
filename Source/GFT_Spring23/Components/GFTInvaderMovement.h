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

	// Callback used for MovementTimer
	UFUNCTION()
	void PerformMove();

private:
	// The rate in seconds when movement should be performed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|InvaderMovement", meta=(AllowPrivateAccess = "true"))
	float MovementRate = 5.f;

	// The vector where the next movement will end
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GFT|InvaderMovement", meta=(AllowPrivateAccess = "true"))
	FVector MovementVector = FVector(0.f, 0.f, 0.f);

	FTimerHandle MovementTimer;
};