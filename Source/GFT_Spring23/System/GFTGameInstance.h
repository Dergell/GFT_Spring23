// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GFT_Spring23/Interfaces/GFTMainMenuInterface.h"
#include "GFTGameInstance.generated.h"

class UGFTSaveGame;
class UGFTMainMenu;

/**
 * The game instance will take care of actions affecting the whole game like loading levels and quitting.
 */
UCLASS()
class GFT_SPRING23_API UGFTGameInstance : public UGameInstance, public IGFTMainMenuInterface
{
	GENERATED_BODY()

public:
	// Overrides from UGameInstance 
	virtual void Init() override;
	virtual void Shutdown() override;

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

	// Update the Highscore in the SaveGame
	void UpdateHighscore(float InHighscore);

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
	UPROPERTY()
	TObjectPtr<UGFTMainMenu> MainMenu;

	// SaveGame object that holds the highscore
	UPROPERTY()
	TObjectPtr<UGFTSaveGame> SaveGame;

	// The stage increases everytime the level is cleared
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Stage = 1;
};