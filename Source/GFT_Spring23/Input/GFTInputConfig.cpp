// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTInputConfig.h"

#include "InputAction.h"

const UInputMappingContext* UGFTInputConfig::GetInputMapping() const
{
	if (!InputMapping)
	{
		UE_LOG(LogInput, Warning, TEXT("InputMapping not configured properly. Inputs may be limited."));
		return nullptr;
	}

	return InputMapping;
}

const UInputAction* UGFTInputConfig::GetInputAction(FName ActionName) const
{
	FProperty* Property = StaticClass()->FindPropertyByName(FName(TEXT("Input") + ActionName.ToString()));
	if (Property == nullptr)
	{
		return nullptr;
	}

	const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property);
	if (ObjectProperty == nullptr)
	{
		return nullptr;
	}

	const void* PropertyAddress = Property->ContainerPtrToValuePtr<void>(this);
	return Cast<UInputAction>(ObjectProperty->GetObjectPropertyValue(PropertyAddress));
}