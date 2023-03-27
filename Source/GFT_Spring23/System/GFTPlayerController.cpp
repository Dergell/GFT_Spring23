// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GFT_Spring23/Input/GFTInputConfig.h"
#include "GFT_Spring23/Pawns/GFTPaddle.h"

void AGFTPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	AGFTPaddle* PaddlePawn = Cast<AGFTPaddle>(aPawn);
	if (PaddlePawn == nullptr)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("This PlayerController is designed to possess AGFTPaddle, please check."));
		return;
	}

	Paddle = PaddlePawn;
	BindInputActions();
}

void AGFTPlayerController::OnUnPossess()
{
	if (Paddle)
	{
		const UGFTInputConfig* InputConfig = Paddle->GetInputConfig();
		if (InputConfig != nullptr)
		{
			RemoveInputMapping(InputConfig->GetInputMapping());
		}

		Paddle = nullptr;
	}

	Super::OnUnPossess();
}

void AGFTPlayerController::BindInputActions()
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (Input == nullptr || !Paddle)
	{
		return;
	}

	const UGFTInputConfig* InputConfig = Paddle->GetInputConfig();
	if (InputConfig != nullptr)
	{
		AddInputMapping(InputConfig->GetInputMapping());
		Input->BindAction(InputConfig->GetInputMove(), ETriggerEvent::Triggered, Paddle.Get(), &AGFTPaddle::MovePaddle);
		Input->BindAction(InputConfig->GetInputFire(), ETriggerEvent::Triggered, Paddle.Get(), &AGFTPaddle::FireBall);
	}
}

void AGFTPlayerController::AddInputMapping(const UInputMappingContext* InputMapping)
{
	if (InputMapping == nullptr)
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer == nullptr)
	{
		UE_LOG(LogPlayerController, Warning, TEXT("Player Controller doesn't have a Local Player."));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSystem != nullptr)
	{
		InputSystem->AddMappingContext(InputMapping, 1);
	}
}

void AGFTPlayerController::RemoveInputMapping(const UInputMappingContext* InputMapping)
{
	if (InputMapping == nullptr)
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSystem != nullptr)
	{
		InputSystem->RemoveMappingContext(InputMapping);
	}
}