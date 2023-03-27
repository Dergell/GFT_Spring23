// Fill out your copyright notice in the Description page of Project Settings.

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
	const UInputAction* GetInputMove() const;
	const UInputAction* GetInputFire() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputFire;
};