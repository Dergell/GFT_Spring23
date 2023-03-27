// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GFTPlayerController.generated.h"

class AGFTPaddle;
class UInputMappingContext;

UCLASS()
class GFT_SPRING23_API AGFTPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	void BindInputActions();
	void AddInputMapping(const UInputMappingContext* InputMapping);
	void RemoveInputMapping(const UInputMappingContext* InputMapping);

	UPROPERTY(VisibleInstanceOnly)
	TObjectPtr<AGFTPaddle> Paddle;
};