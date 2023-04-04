// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GFT_Spring23/Interfaces/GFTMainMenuInterface.h"
#include "GFTGameInstance.generated.h"

class UGFTMainMenu;

/**
 * The game instance will take care of actions affecting the whole game like loading levels and quitting.
 */
UCLASS()
class GFT_SPRING23_API UGFTGameInstance : public UGameInstance, public IGFTMainMenuInterface
{
	GENERATED_BODY()

public:
	// This will display the main menu
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	// Transition to the main menu level
	UFUNCTION(BlueprintCallable)
	void LoadMenuLevel();

	// Get current Stage
	int32 GetStage() const;

	// Advance Stage
	void AdvanceStage();

protected:
	// Quit the game
	virtual void Quit() override;

	// Load the main level
	virtual void Play() override;

	// Blueprint widget used as main menu
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT)
	TSubclassOf<UUserWidget> MainMenuClass;

	// Level to be loaded on play
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT)
	TSoftObjectPtr<UWorld> MainLevel;

	// Level to be loaded on game over
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT)
	TSoftObjectPtr<UWorld> MenuLevel;

private:
	// Remember the main menu, so we can shut it down later 
	TObjectPtr<UGFTMainMenu> MainMenu;

	// The stage increases everytime the level is cleared
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Stage = 1;
};