// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GFTImpactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UGFTImpactable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface can be implemented by anything in need to react to impacts.
 */
class GFT_SPRING23_API IGFTImpactable
{
	GENERATED_BODY()

public:
	// Implement this method to handle ball impacts
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void BallImpact();

	// Implement this method to handle projectile impacts
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void ProjectileImpact();
};