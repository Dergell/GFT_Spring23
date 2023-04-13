// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTInputConfig.h"

const UInputMappingContext* UGFTInputConfig::GetInputMapping() const
{
	if (!InputMapping)
	{
		UE_LOG(LogInput, Warning, TEXT("InputMapping not configured properly. Inputs may be limited."));
		return nullptr;
	}

	return InputMapping;
}

const UInputAction* UGFTInputConfig::GetInputMove() const
{
	if (!InputMove)
	{
		UE_LOG(LogInput, Warning, TEXT("InputMove not configured properly. Inputs may be limited."));
		return nullptr;
	}

	return InputMove;
}

const UInputAction* UGFTInputConfig::GetInputFire() const
{
	if (!InputFire)
	{
		UE_LOG(LogInput, Warning, TEXT("InputFire not configured properly. Inputs may be limited."));
		return nullptr;
	}

	return InputFire;
}