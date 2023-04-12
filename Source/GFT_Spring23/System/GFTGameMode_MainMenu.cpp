// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTGameMode_MainMenu.h"

#include "GFTGameInstance.h"

void AGFTGameMode_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	UGFTGameInstance* Instance = GetGameInstance<UGFTGameInstance>();
	if (Instance != nullptr)
	{
		Instance->LoadMenu();
	}
}