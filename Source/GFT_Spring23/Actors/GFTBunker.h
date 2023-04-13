// Brick Invaders - Copyright (C) 2023 Tony Schmich

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
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// React to a ball impact
	virtual void BallImpact_Implementation() override;

	// React to a projectile impact
	virtual void ProjectileImpact_Implementation() override;

	// Will reduce the size of he bunker by the DamageScalar
	virtual void HandleHit();

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