// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTBall.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AGFTBall::AGFTBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("BlockAll"));
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetUseCCD(true);
	Collision->SetEnableGravity(false);
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetGenerateOverlapEvents(false);

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Projectile->ProjectileGravityScale = 0.f;
	Projectile->bRotationFollowsVelocity = true;
	Projectile->bShouldBounce = true;
	Projectile->Bounciness = 1.f;
	Projectile->Friction = 0.f;
	Projectile->BounceVelocityStopSimulatingThreshold = 5.f;
	Projectile->MaxSimulationIterations = 12;
	Projectile->bInterpMovement = true;
	Projectile->bInterpRotation = true;
	Projectile->bConstrainToPlane = true;
	Projectile->SetPlaneConstraintNormal(FVector(1.f, 0.f, 0.f));
}