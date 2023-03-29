// Fill out your copyright notice in the Description page of Project Settings.


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