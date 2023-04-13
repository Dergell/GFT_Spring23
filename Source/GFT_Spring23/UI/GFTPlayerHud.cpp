// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTPlayerHud.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"
#include "GFT_Spring23/System/GFTPlayerState.h"

bool UGFTPlayerHud::Initialize()
{
	bool Result = Super::Initialize();
	if (!Result)
	{
		return Result;
	}

	UpdateLives();
	UpdateScore();

	return Result;
}

void UGFTPlayerHud::UpdateLives()
{
	AGFTPlayerState* State = GetOwningPlayerState<AGFTPlayerState>();
	if (TextLivesValue != nullptr && State != nullptr)
	{
		TextLivesValue->SetText(FText::AsNumber(State->GetLives()));
	}
}

void UGFTPlayerHud::UpdateScore()
{
	AGFTPlayerState* State = GetOwningPlayerState<AGFTPlayerState>();
	if (TextScoreValue != nullptr && State != nullptr)
	{
		TextScoreValue->SetText(FText::AsNumber(State->GetScore()));
	}
}