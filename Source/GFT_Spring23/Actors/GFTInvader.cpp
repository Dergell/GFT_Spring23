// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvader.h"

#include "GFTProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GFT_Spring23/Interfaces/GFTGameFramework.h"
#include "Kismet/GameplayStatics.h"

AGFTInvader::AGFTInvader()
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

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Collision);
}

bool AGFTInvader::HasClearShot()
{
	FVector Start = Muzzle->GetComponentLocation();
	FVector End = Muzzle->GetComponentLocation() + Muzzle->GetForwardVector() * 1000;
	TArray<FHitResult> Hits;
	FCollisionQueryParams CollisionQuery;
	CollisionQuery.AddIgnoredActor(this);
	GetWorld()->LineTraceMultiByChannel(Hits, Start, End, ECC_WorldDynamic, CollisionQuery);

	for (FHitResult Hit : Hits)
	{
		if (Hit.GetActor()->IsA(StaticClass()))
		{
			return false;
		}
	}

	return true;
}

void AGFTInvader::Shoot()
{
	if (ProjectileClass == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("ProjectileClass not set in %s, cannot shoot."), *GetName());
		return;
	}

	GetWorld()->SpawnActor<AGFTProjectile>(ProjectileClass, Muzzle->GetComponentLocation(), FRotator::ZeroRotator);
}

void AGFTInvader::BallImpact_Implementation()
{
	Destroy();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController != nullptr && PlayerController->Implements<UGFTGameFramework>())
	{
		IGFTGameFramework::Execute_ScoreUpdate(PlayerController, Points);
	}
}