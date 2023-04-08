// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTBunker.h"

#include "Components/BoxComponent.h"

AGFTBunker::AGFTBunker()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collision->SetEnableGravity(false);
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetGenerateOverlapEvents(false);
}

void AGFTBunker::HandleHit()
{
	if (GetActorScale3D().GetMin() >= 0)
	{
		SetActorScale3D(GetActorScale3D() - DamageScalar);
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