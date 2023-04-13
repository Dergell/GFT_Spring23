// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GFTGameMode_MainMenu.generated.h"

class UGFTMainMenu;

/**
 * GameMode used for the MainMenu level
 */
UCLASS()
class GFT_SPRING23_API AGFTGameMode_MainMenu : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};