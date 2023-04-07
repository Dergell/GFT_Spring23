// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GFTEnemy.h"
#include "GFTMothership.generated.h"

/**
 * Class for the mothership (i.e. UFO) that will spawn randomly and move across the top of the screen.
 * Can be destroyed by the player for bonus points.
 */
UCLASS(Blueprintable, NotPlaceable)
class GFT_SPRING23_API AGFTMothership : public AGFTEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTMothership();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Direction and speed of movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	FVector Velocity;
};