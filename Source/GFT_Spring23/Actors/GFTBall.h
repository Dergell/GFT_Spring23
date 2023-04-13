// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTBall.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GFT_SPRING23_API AGFTBall : public AActor
{
	GENERATED_BODY()

public:
	AGFTBall();

protected:
	virtual void BeginPlay() override;

	// Callback when we end an overlap
	UFUNCTION()
	void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Callback when we hit something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// After a hit, we check our velocity to prevent the horizontal ball problem
	UFUNCTION()
	void CheckVelocity();

private:
	// Sphere used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// This will drive the movement of the ball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> Projectile;

	// Minimal Vertical Velocity, so the ball will never get stuck in a boring horizontal path
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float MinVerticalVelocity = 300.f;
};