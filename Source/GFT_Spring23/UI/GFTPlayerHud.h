// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFTPlayerHud.generated.h"

class UTextBlock;

/**
 * Widget used to display the players HUD
 */
UCLASS()
class GFT_SPRING23_API UGFTPlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:
	// Setup
	virtual bool Initialize() override;

	// Update text values with current values from PlayerState
	void UpdateLives();
	void UpdateScore();

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextScoreValue;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextLivesValue;
};