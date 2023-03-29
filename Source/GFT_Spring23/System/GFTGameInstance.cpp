// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "GFT_Spring23/UI/GFTMainMenu.h"

void UGFTGameInstance::LoadMenu()
{
	if (MainMenuClass == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("No MainMenuClass set in GameInstance."));
		return;
	}

	MainMenu = CreateWidget<UGFTMainMenu>(this, MainMenuClass);
	if (MainMenu != nullptr)
	{
		MainMenu->Setup();
		MainMenu->SetInterface(this);
	}
}

void UGFTGameInstance::Quit()
{
	// Seems like this is how to do it, according to UKismetSystemLibrary::QuitGame
	GetFirstLocalPlayerController()->ConsoleCommand("quit");
}

void UGFTGameInstance::Play()
{
	const FString LevelPath = MainLevel.GetLongPackageName();
	if (LevelPath.IsEmpty())
	{
		UE_LOG(LogLevel, Warning, TEXT("No MainLevel set in GameInstance."));
		return;
	}

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		World->ServerTravel(LevelPath);
	}

	if (MainMenu != nullptr)
	{
		MainMenu->Shutdown();
	}
}