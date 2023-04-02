// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTBunker.generated.h"

class UBoxComponent;

UCLASS()
class GFT_SPRING23_API AGFTBunker : public AActor, public IGFTImpactable
{
	GENERATED_BODY()

public:
	AGFTBunker();

protected:
	virtual void TakeDamage();

private:
	// React to a ball impact
	virtual void BallImpact_Implementation() override;

	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Each time the bunker is damaged, it will scale down by this value to represent damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float DamageScalar = 0.1f;
};