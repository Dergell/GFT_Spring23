// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvader.h"

#include "GFTProjectile.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AGFTInvader::AGFTInvader()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Muzzle = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Collision);
}

bool AGFTInvader::HasClearShot()
{
	// Trace downwards from the muzzle
	const FVector Start = Muzzle->GetComponentLocation();
	const FVector End = Muzzle->GetComponentLocation() + Muzzle->GetForwardVector() * 1000;
	TArray<FHitResult> Hits;
	GetWorld()->LineTraceMultiByChannel(Hits, Start, End, ECC_WorldDynamic);

	// Only other invaders will block shooting
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