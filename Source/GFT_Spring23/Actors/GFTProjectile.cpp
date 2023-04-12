// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"

AGFTProjectile::AGFTProjectile()
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
	Projectile->bRotationFollowsVelocity = false;
	Projectile->bShouldBounce = false;
	Projectile->MaxSimulationIterations = 12;
	Projectile->bInterpMovement = true;
	Projectile->bInterpRotation = true;
	Projectile->bConstrainToPlane = true;
	Projectile->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
}

void AGFTProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorEndOverlap.AddDynamic(this, &AGFTProjectile::OnEndOverlap);
	Collision->OnComponentHit.AddDynamic(this, &AGFTProjectile::OnHit);
}

void AGFTProjectile::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("GameSpace")))
	{
		Destroy();
	}
}

void AGFTProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();

	if (OtherActor != nullptr && OtherActor->Implements<UGFTImpactable>())
	{
		IGFTImpactable::Execute_ProjectileImpact(OtherActor);
	}
}