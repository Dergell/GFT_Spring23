// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GFTInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Input Config Data Asset for Paddles
 */
UCLASS()
class GFT_SPRING23_API UGFTInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputMappingContext* GetInputMapping() const;
	const UInputAction* GetInputAction(FName ActionName) const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputFire;
};