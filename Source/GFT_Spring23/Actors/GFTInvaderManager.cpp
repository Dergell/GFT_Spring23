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
			FTransform SpawnTransform = FTransform(SpawnLocation);
			UChildActorComponent* ChildComponent = Cast<UChildActorComponent>(
				AddComponentByClass(UChildActorComponent::StaticClass(), false, SpawnTransform, false)
			);
			ChildComponent->SetChildActorClass(InvaderClass);
			SpawnLocation.Z += RowDistance;
		}
		SpawnLocation.Z = RowDistance / 2;
		SpawnLocation.X += ColumnDistance;
	}
}