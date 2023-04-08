// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GFTSaveGame.generated.h"

/**
 * This class is holding all data meant to be saved to disk
 */
UCLASS()
class GFT_SPRING23_API UGFTSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	float GetHighscore() const;
	void SetHighscore(float InHighscore);

private:
	// The highscore achieved on this local computer
	UPROPERTY()
	float Highscore = 0.f;
};