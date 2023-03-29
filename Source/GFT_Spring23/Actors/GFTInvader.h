// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTInvader.generated.h"

class UBoxComponent;

UCLASS()
class GFT_SPRING23_API AGFTInvader : public AActor, public IGFTImpactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTInvader();

	// React to a ball impact
	virtual void BallImpact_Implementation() override;

private:
	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// How many points this invader is worth once destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Points = 100;
};