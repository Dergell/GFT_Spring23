// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTBunker.h"

#include "GFTInvader.h"
#include "Components/BoxComponent.h"

AGFTBunker::AGFTBunker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collision->SetEnableGravity(false);
	Collision->SetCollisionObjectType(ECC_GameTraceChannel4); // Custom Object Type "Bunker"
	Collision->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap); // Overlap "Invader" type
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetGenerateOverlapEvents(false);
}

void AGFTBunker::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AGFTBunker::OnBeginOverlap);
}

void AGFTBunker::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AGFTInvader::StaticClass()))
	{
		SetActorScale3D(FVector::ZeroVector);
		SetActorEnableCollision(false);
	}
}

void AGFTBunker::BallImpact_Implementation()
{
	HandleHit();
}

void AGFTBunker::ProjectileImpact_Implementation()
{
	HandleHit();
}

void AGFTBunker::HandleHit()
{
	if (GetActorScale3D().GetMin() > DamageScalar)
	{
		SetActorScale3D(GetActorScale3D() - DamageScalar);
	}
	else
	{
		SetActorScale3D(FVector::ZeroVector);
		SetActorEnableCollision(false);
	}
}