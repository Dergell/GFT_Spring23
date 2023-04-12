// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTMothership.h"

#include "Kismet/GameplayStatics.h"

AGFTMothership::AGFTMothership()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGFTMothership::BeginPlay()
{
	Super::BeginPlay();

	if (StartSound != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, StartSound);
	}
}

void AGFTMothership::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
}