// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTInvaderManager.generated.h"

class UGFTInvaderMovement;
class AGFTInvader;

/*
 * This class allows easy placement of multiple invaders on the map and keeps them grouped for simple movement.
 */
UCLASS()
class GFT_SPRING23_API AGFTInvaderManager : public AActor
{
	GENERATED_BODY()

public:
	AGFTInvaderManager();

	// Will be called on every single creation or update of the actor, even in editor
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	// Billboard used as root, so we can see the actor in editor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBillboardComponent> Billboard;

	// Component responsible for moving the invaders
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGFTInvaderMovement> InvaderMovement;

	// Allows selection if blueprint used for spawning
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AGFTInvader> InvaderClass;

	// Position of the editor utility widget 
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true", MakeEditWidget = "true"))
	FVector WidgetPosition;

	// ColumnsDistance determines how many columns of invaders are spawned
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float ColumnDistance = 100.f;

	// RowDistance determines how many invaders fit in each column
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float RowDistance = 100.f;
};