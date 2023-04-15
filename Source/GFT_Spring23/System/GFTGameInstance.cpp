// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTGameInstance.h"

#include "GFTSaveGame.h"
#include "Blueprint/UserWidget.h"
#include "GFT_Spring23/UI/GFTMainMenu.h"
#include "Kismet/GameplayStatics.h"

void UGFTGameInstance::Init()
{
	Super::Init();

	if (UGameplayStatics::DoesSaveGameExist(TEXT("local"), 0))
	{
		SaveGame = Cast<UGFTSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("local"), 0));
	}
	else
	{
		SaveGame = Cast<UGFTSaveGame>(UGameplayStatics::CreateSaveGameObject(UGFTSaveGame::StaticClass()));
	}
}

void UGFTGameInstance::Shutdown()
{
	if (SaveGame != nullptr)
	{
		UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("local"), 0);
	}

	Super::Shutdown();
}

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

		if (SaveGame != nullptr)
		{
			MainMenu->UpdateHighscore(SaveGame->GetHighscore());
		}
	}
}

void UGFTGameInstance::LoadMenuLevel()
{
	const FString LevelPath = MenuLevel.GetLongPackageName();
	if (LevelPath.IsEmpty())
	{
		UE_LOG(LogLevel, Warning, TEXT("No MenuLevel set in GameInstance."));
		return;
	}

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		World->ServerTravel(LevelPath);
	}
}

void UGFTGameInstance::UpdateHighscore(float InHighscore)
{
	if (SaveGame != nullptr && SaveGame->GetHighscore() <= InHighscore)
	{
		SaveGame->SetHighscore(InHighscore);
	}
}

void UGFTGameInstance::Quit()
{
	// Seems like this is how to do it, according to UKismetSystemLibrary::QuitGame
	GetFirstLocalPlayerController()->ConsoleCommand("quit");
}

void UGFTGameInstance::Play()
{
	if (MainMenu != nullptr)
	{
		MainMenu->Shutdown();
	}

	const FString LevelPath = MainLevel.GetLongPackageName();
	if (LevelPath.IsEmpty())
	{
		UE_LOG(LogLevel, Warning, TEXT("No MainLevel set in GameInstance."));
		return;
	}

	UWorld* World = GetWorld();
	if (World != nullptr && MainLevel != World)
	{
		World->ServerTravel(LevelPath);
	}
}