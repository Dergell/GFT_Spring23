// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTPaddle.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GFT_Spring23/Actors/GFTBall.h"
#include "GFT_Spring23/Input/GFTInputConfig.h"
#include "GFT_Spring23/Interfaces/GFTGameFramework.h"
#include "GFT_Spring23/System/GFTGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGFTPaddle::AGFTPaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

	PaddleAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("PaddleAnchor"));
	PaddleAnchor->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(PaddleAnchor);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetGenerateOverlapEvents(false);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetupAttachment(PaddleAnchor);
	Capsule->SetCollisionProfileName(TEXT("BlockAll"));
	Capsule->SetUseCCD(true);

	BallSpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BallSpawnArrow"));
	BallSpawnArrow->SetupAttachment(PaddleAnchor);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

UGFTInputConfig* AGFTPaddle::GetInputConfig() const
{
	if (InputConfig.IsNull())
	{
		return nullptr;
	}

	return InputConfig.LoadSynchronous();
}

void AGFTPaddle::MovePaddle(const FInputActionInstance& Instance)
{
	const float InputValue = Instance.GetValue().Get<float>();
	PositionOnSpline += InputValue / MovementSensitivity;
	PositionOnSpline = FMath::Clamp(PositionOnSpline, 0.f, 1.f);

	float DistanceOnSpline = PositionOnSpline * Spline->GetSplineLength();
	FTransform Transform = Spline->GetTransformAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World);
	PaddleAnchor->SetWorldTransform(Transform);
}

void AGFTPaddle::FireBall()
{
	AGFTGameMode* GameMode = Cast<AGFTGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode == nullptr)
	{
		return;
	}

	if (GameMode->IsBallReady() && GameMode->GetBallClass() != nullptr)
	{
		FActorSpawnParameters Params;
		Params.Owner = GetController();
		Params.Instigator = this;
		GetWorld()->SpawnActor<AGFTBall>(GameMode->GetBallClass(), BallSpawnArrow->GetComponentTransform(), Params);
		GameMode->AddActiveBall();
	}
}

void AGFTPaddle::ProjectileImpact_Implementation()
{
	if (ExplosionSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, ExplosionSound);
	}

	if (Controller != nullptr && Controller->Implements<UGFTGameFramework>())
	{
		IGFTGameFramework::Execute_PaddleLost(Controller);
	}
}