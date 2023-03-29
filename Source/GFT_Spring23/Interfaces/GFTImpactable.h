// Fill out your copyright notice in the Description page of Project Settings.

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
 * Interface can be implemented by anything in need to react to ball impacts.
 */
class GFT_SPRING23_API IGFTImpactable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=GFT)
	void BallImpact();
};