// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvaderManager.h"

#include "GFTInvader.h"
#include "Components/BillboardComponent.h"
#include "GFT_Spring23/Components/GFTInvaderMovement.h"

AGFTInvaderManager::AGFTInvaderManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	RootComponent = Billboard;

	InvaderMovement = CreateDefaultSubobject<UGFTInvaderMovement>(TEXT("InvaderMovement"));
}

void AGFTInvaderManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Calculate how many columns and rows are needed
	const int ColumnCount = FMath::TruncToInt(WidgetPosition.X / ColumnDistance);
	const int RowCount = FMath::TruncToInt(WidgetPosition.Z / RowDistance);

	// Using the halved distances for initial location keeps all invaders between the manager and widget locations 
	FVector SpawnLocation = FVector(ColumnDistance / 2, 0, RowDistance / 2);

	for (int CurrentColumn = 0; CurrentColumn < ColumnCount; ++CurrentColumn)
	{
		for (int CurrentRow = 0; CurrentRow < RowCount; ++CurrentRow)
		{
			// Add new child component and set class
			UChildActorComponent* ChildComponent = Cast<UChildActorComponent>(
				AddComponentByClass(UChildActorComponent::StaticClass(), false, FTransform(SpawnLocation), false)
			);
			ChildComponent->SetChildActorClass(InvaderClass);

			// Register callbacks on the child
			AGFTInvader* Invader = Cast<AGFTInvader>(ChildComponent->GetChildActor());
			Invader->OnInvaderLeavingVolume.AddDynamic(this, &AGFTInvaderManager::OnInvaderLeavingVolume);
			Invader->OnDestroyed.AddDynamic(this, &AGFTInvaderManager::OnInvaderDestroyed);

			SpawnLocation.Z += RowDistance;
		}
		SpawnLocation.Z = RowDistance / 2;
		SpawnLocation.X += ColumnDistance;
	}
}

void AGFTInvaderManager::OnInvaderLeavingVolume(AActor* Invader, AActor* Volume)
{
	FVector Origin, Extends;
	Volume->GetActorBounds(false, Origin, Extends);
	const FVector InvaderLocation = Invader->GetActorLocation();

	// If we leave the volume at the bottom, stop downward movement
	if (InvaderLocation.Z <= Origin.Z - Extends.Z)
	{
		InvaderMovement->SetShouldMoveDown(false);
	}

	// If we leave the volume left or right, revert movement vector
	if (InvaderLocation.X >= Origin.X + Extends.X || InvaderLocation.X <= Origin.X - Extends.X)
	{
		InvaderMovement->RevertMovementVector();
	}
}

void AGFTInvaderManager::OnInvaderDestroyed(AActor* DestroyedActor)
{
	// Check if we are in game to prevent value change in editor
	if (!GetWorld()->IsGameWorld())
	{
		return;
	}

	InvaderMovement->DecreaseMovementRate();
}