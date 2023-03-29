// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFTMainMenu.generated.h"

class IGFTMainMenuInterface;
class UButton;

/**
 * Widget used to display the main menu
 */
UCLASS()
class GFT_SPRING23_API UGFTMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UGFTMainMenu(const FObjectInitializer& ObjectInitializer);

	// Here we can setup event delegates
	virtual bool Initialize() override;

	// Setter
	void SetInterface(IGFTMainMenuInterface* Interface);

	// This will display the widget
	void Setup();
	// This will hide it again
	void Shutdown();

protected:
	// Callback for ButtonPlay
	UFUNCTION()
	void OnPlay();

	// Callback for ButtonQuit
	UFUNCTION()
	void OnQuit();

	// Directly binds to the blueprint button ButtonPlay
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ButtonPlay;

	// Directly binds to the blueprint button ButtonQuit
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ButtonQuit;

private:
	// This will hold the interface used for actions
	IGFTMainMenuInterface* MenuInterface;
};