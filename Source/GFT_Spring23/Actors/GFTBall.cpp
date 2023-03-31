// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTBall.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"

AGFTBall::AGFTBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetUseCCD(true);
	Collision->SetEnableGravity(false);
	Collision->SetNotifyRigidBodyCollision(true);
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
	Projectile->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
}

void AGFTBall::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &AGFTBall::OnHit);
}

void AGFTBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor->Implements<UGFTImpactable>())
	{
		IGFTImpactable::Execute_BallImpact(OtherActor);
	}
}