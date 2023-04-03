// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTInvader.generated.h"

class UArrowComponent;
class AGFTProjectile;
class UBoxComponent;

UCLASS()
class GFT_SPRING23_API AGFTInvader : public AActor, public IGFTImpactable
{
	GENERATED_BODY()

public:
	AGFTInvader();

	// Returns true if no other Invader would block an attack
	bool HasClearShot();

	// Spawn a projectile at the Muzzle and send it away
	void Shoot();

private:
	// React to a ball impact
	virtual void BallImpact_Implementation() override;

	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Arrow used as starting position of projectiles
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Muzzle;

	// How many points this invader is worth once destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Points = 100;

	// Blueprint class to use when spawning a Ball
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AGFTProjectile> ProjectileClass;
};