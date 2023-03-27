// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GFTPaddle.generated.h"

class UArrowComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputAction;
class UInputMappingContext;
class USplineComponent;
struct FInputActionInstance;

UCLASS()
class GFT_SPRING23_API AGFTPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGFTPaddle();

	// Called when the pawn is possessed
	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MovePaddle(const FInputActionInstance& Instance);

private:
	void SetupMappingContext(const APlayerController* PlayerController);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneRoot;
	
	// Scene component used to move the paddle independent of Camera & Spline
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

	UPROPERTY(EditAnywhere, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditAnywhere, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSoftObjectPtr<UInputAction> InputActionMove;

	float PositionOnSpline = 0.5f;
};