// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GFTGameFramework.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGFTGameFramework : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for generic game events, like score changes or lost balls
 */
class GFT_SPRING23_API IGFTGameFramework
{
	GENERATED_BODY()

public:
	// Can be used whenever the score needs to be updated
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void ScoreUpdate(int32 Points);

	// Executed when a Ball leaves the GameSpace trigger volume
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void BallLost();

	// Executed when the paddle got shot by an invader
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void PaddleLost();
};