// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTEnemy.generated.h"

class UBoxComponent;

/**
 * Abstract base class for enemies. Provides basic components for Mesh and Collision,
 * as well as functionality when leaving the GameSpace or giving points when destroyed.
 */
UCLASS(Abstract, NotBlueprintable)
class GFT_SPRING23_API AGFTEnemy : public AActor, public IGFTImpactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Callback whenever we end an overlap
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// React to a ball impact
	virtual void BallImpact_Implementation() override;

protected:
	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT)
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT)
	TObjectPtr<UStaticMeshComponent> Mesh;

private:
	// Explosion sound file
	UPROPERTY(EditDefaultsOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundWave> ExplosionSound;
	
	// How many points this enemy is worth once destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Points = 100;
};