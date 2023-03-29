// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GFT_Spring23/Interfaces/GFTGameFramework.h"
#include "GFTPlayerController.generated.h"

class UGFTPlayerHud;
class AGFTPaddle;
class UInputMappingContext;

UCLASS()
class GFT_SPRING23_API AGFTPlayerController : public APlayerController, public IGFTGameFramework
{
	GENERATED_BODY()

protected:
	// Generic overrides
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	// Implementations from IGFTGameFramework
	virtual void ScoreUpdate_Implementation(int32 Points) override;
	virtual void BallLost_Implementation() override;

private:
	// Input operatrions
	void BindInputActions();
	void AddInputMapping(const UInputMappingContext* InputMapping);
	void RemoveInputMapping(const UInputMappingContext* InputMapping);

	// Blueprints used as player hud
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UGFTPlayerHud> HudClass;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AGFTPaddle> Paddle;

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<UGFTPlayerHud> HudWidget;
};