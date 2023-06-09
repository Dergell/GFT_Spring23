// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTPaddle.generated.h"

class UArrowComponent;
class UCameraComponent;
class UCapsuleComponent;
class UGFTInputConfig;
class UInputMappingContext;
class USplineComponent;
struct FInputActionInstance;

/**
 * Paddle representing the player, used the shoot and bounce back balls.
 */
UCLASS()
class GFT_SPRING23_API AGFTPaddle : public APawn, public IGFTImpactable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGFTPaddle();

	// Getters
	UGFTInputConfig* GetInputConfig() const;

	// Actions
	void MovePaddle(const FInputActionInstance& Instance);
	void FireBall();

private:
	// Handle getting shot by an invader
	virtual void ProjectileImpact_Implementation() override;

	// Used as RootComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;

	// Scene component used to move the paddle independent of Camera & Spline attach to SceneRoot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> PaddleAnchor;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Capsule used for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> Capsule;

	// Arrow used set starting position of new ball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> BallSpawnArrow;

	// Movement only possible along Spline
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	// Input configuration for this pawn
	UPROPERTY(EditAnywhere, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UGFTInputConfig> InputConfig;

	// Explosion sound file
	UPROPERTY(EditDefaultsOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundWave> ExplosionSound;

	// The higher this value, the softer any movements will be
	UPROPERTY(EditDefaultsOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float MovementSensitivity = 100.f;

	// Current position of the PaddleAnchor along the Spline
	UPROPERTY(VisibleInstanceOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	float PositionOnSpline = 0.5f;
};