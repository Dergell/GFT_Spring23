// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTMainMenu.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GFT_Spring23/Interfaces/GFTMainMenuInterface.h"

UGFTMainMenu::UGFTMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	this->bIsFocusable = true;
}

bool UGFTMainMenu::Initialize()
{
	bool Result = Super::Initialize();
	if (!Result)
	{
		return Result;
	}

	if (ButtonPlay != nullptr)
	{
		ButtonPlay->OnClicked.AddDynamic(this, &UGFTMainMenu::OnPlay);
	}

	if (ButtonQuit != nullptr)
	{
		ButtonQuit->OnClicked.AddDynamic(this, &UGFTMainMenu::OnQuit);
	}

	return Result;
}

void UGFTMainMenu::SetInterface(IGFTMainMenuInterface* Interface)
{
	MenuInterface = Interface;
}

void UGFTMainMenu::Setup()
{
	this->AddToViewport();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputModeData);
		PlayerController->bShowMouseCursor = true;
	}
}

void UGFTMainMenu::Shutdown()
{
	this->RemoveFromParent();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController != nullptr)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
}

void UGFTMainMenu::UpdateHighscore(float InHighscore)
{
	if (TextHighscoreValue != nullptr)
	{
		TextHighscoreValue->SetText(FText::AsNumber(InHighscore));
	}
}

void UGFTMainMenu::OnPlay()
{
	if (ensure(MenuInterface != nullptr))
	{
		MenuInterface->Play();
	}
}

void UGFTMainMenu::OnQuit()
{
	if (ensure(MenuInterface != nullptr))
	{
		MenuInterface->Quit();
	}
}