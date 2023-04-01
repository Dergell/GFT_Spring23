// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvaderMovement.h"

UGFTInvaderMovement::UGFTInvaderMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UGFTInvaderMovement::RevertMovementVector()
{
	if (bWasReverted)
	{
		return;
	}

	if (bShouldMoveDown)
	{
		MovementVector.Z = -FMath::Abs(MovementVector.X);
	}

	MovementVector.X *= -1;
	bWasReverted = true;
}

void UGFTInvaderMovement::SetShouldMoveDown(bool bInShouldMoveDown)
{
	bShouldMoveDown = bInShouldMoveDown;
}

void UGFTInvaderMovement::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &UGFTInvaderMovement::PerformMove, MovementRate, true);
}

void UGFTInvaderMovement::PerformMove()
{
	const FVector Location = GetOwner()->GetActorLocation();
	FVector NewLocation = Location;

	// If there's any downward movement, perform and remove it
	if (MovementVector.Z != 0)
	{
		NewLocation.Z += MovementVector.Z;
		MovementVector.Z = 0;
	}
	// only do horizontal movement if there no downward movement needed
	else
	{
		NewLocation.X += MovementVector.X;
	}

	GetOwner()->SetActorLocation(NewLocation);
	bWasReverted = false;
}