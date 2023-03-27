// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTPaddle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGFTPaddle::AGFTPaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void AGFTPaddle::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (const APlayerController* PlayerController = Cast<APlayerController>(NewController))
	{
		SetupMappingContext(PlayerController);
	}
}

// Called when the game starts or when spawned
void AGFTPaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGFTPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGFTPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (Input == nullptr || InputActionMove.IsNull())
	{
		return;
	}

	Input->BindAction(InputActionMove.LoadSynchronous(), ETriggerEvent::Triggered, this, &AGFTPaddle::MovePaddle);
}

void AGFTPaddle::MovePaddle(const FInputActionInstance& Instance)
{
	const float InputValue = Instance.GetValue().Get<float>();
	PositionOnSpline += InputValue / 100;
	PositionOnSpline = FMath::Clamp(PositionOnSpline, 0.f, 1.f);

	float DistanceOnSpline = PositionOnSpline * Spline->GetSplineLength();
	FTransform Transform = Spline->GetTransformAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World);
	PaddleAnchor->SetWorldTransform(Transform);
}

void AGFTPaddle::SetupMappingContext(const APlayerController* PlayerController)
{
	const ULocalPlayer* Player = PlayerController->GetLocalPlayer();
	if (Player == nullptr || InputMapping.IsNull())
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 1);
	}
}