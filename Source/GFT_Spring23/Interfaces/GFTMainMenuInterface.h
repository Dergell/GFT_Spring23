// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GFTMainMenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGFTMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface can be implemented by anything in need to react to main menu actions.
 */
class GFT_SPRING23_API IGFTMainMenuInterface
{
	GENERATED_BODY()

public:
	// Quit the game
	virtual void Quit() = 0;

	// Play the main level
	virtual void Play() = 0;
};