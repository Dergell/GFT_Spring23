﻿// Brick Invaders - Copyright (C) 2023 Tony Schmich

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Direction and speed of movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	FVector Velocity;

	// Sound played when spawned
	UPROPERTY(EditDefaultsOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundWave> StartSound;
};