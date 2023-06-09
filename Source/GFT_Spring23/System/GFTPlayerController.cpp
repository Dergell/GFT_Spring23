// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GFTGameInstance.h"
#include "GFTPlayerState.h"
#include "Blueprint/UserWidget.h"
#include "GFT_Spring23/Input/GFTInputConfig.h"
#include "GFT_Spring23/Pawns/GFTPaddle.h"
#include "GFT_Spring23/UI/GFTPlayerHud.h"

void AGFTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HudClass != nullptr)
	{
		HudWidget = CreateWidget<UGFTPlayerHud>(this, HudClass);
		HudWidget->AddToViewport();
	}

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (LocalPlayer != nullptr)
	{
		LocalPlayer->AspectRatioAxisConstraint = AspectRatio_MaintainYFOV;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	const UGFTInputConfig* InputConfig = Paddle->GetInputConfig();
	if (Input != nullptr && InputConfig != nullptr)
	{
		Input->BindAction(InputConfig->GetInputAction(TEXT("Pause")), ETriggerEvent::Triggered, this, &AGFTPlayerController::TriggerPause);
	}
}

void AGFTPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HudWidget != nullptr)
	{
		HudWidget->RemoveFromParent();
	}
}

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

	const UGFTInputConfig* InputConfig = Paddle->GetInputConfig();
	if (InputConfig != nullptr)
	{
		AddInputMapping(InputConfig->GetInputMapping());
		BindInputActions();
	}
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

void AGFTPlayerController::ScoreUpdate_Implementation(int32 Points)
{
	AGFTPlayerState* State = GetPlayerState<AGFTPlayerState>();
	if (State != nullptr)
	{
		State->UpdateScore(Points);
	}

	if (HudWidget != nullptr)
	{
		HudWidget->UpdateScore();
	}
}

void AGFTPlayerController::BallLost_Implementation()
{
	// Disabled for balancing. Maybe add later as optional hard mode?
	//LoseLive();
}

void AGFTPlayerController::PaddleLost_Implementation()
{
	LoseLive();
	if (GetPawn() != nullptr)
	{
		GetPawn()->Destroy();
	}
	ServerRestartPlayer();
}

void AGFTPlayerController::LoseLive()
{
	AGFTPlayerState* State = GetPlayerState<AGFTPlayerState>();
	if (State == nullptr)
	{
		return;
	}

	OnLiveLost.Broadcast();

	State->SetLives(State->GetLives() - 1);
	if (State->GetLives() <= 0)
	{
		OnGameOver.Broadcast(State);
	}

	if (HudWidget != nullptr)
	{
		HudWidget->UpdateLives();
	}
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
		Input->BindAction(InputConfig->GetInputAction(TEXT("Move")), ETriggerEvent::Triggered, Paddle.Get(), &AGFTPaddle::MovePaddle);
		Input->BindAction(InputConfig->GetInputAction(TEXT("Fire")), ETriggerEvent::Triggered, Paddle.Get(), &AGFTPaddle::FireBall);
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

void AGFTPlayerController::TriggerPause()
{
	Pause();

	UGFTGameInstance* Instance = GetGameInstance<UGFTGameInstance>();
	if (Instance == nullptr)
	{
		return;
	}

	Instance->LoadMenu();
}