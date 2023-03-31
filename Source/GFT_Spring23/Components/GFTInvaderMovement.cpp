// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvaderMovement.h"

UGFTInvaderMovement::UGFTInvaderMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UGFTInvaderMovement::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &UGFTInvaderMovement::PerformMove, MovementRate, true);
}

void UGFTInvaderMovement::PerformMove()
{
	const FVector Location = GetOwner()->GetActorLocation();
	GetOwner()->SetActorLocation(Location + MovementVector);
}