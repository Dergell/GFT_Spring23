// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTMothership.h"

#include "Components/BoxComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AGFTMothership::AGFTMothership()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collision->SetEnableGravity(false);
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->SetGenerateOverlapEvents(false);
}

void AGFTMothership::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentEndOverlap.AddDynamic(this, &AGFTMothership::EndOverlap);
}

void AGFTMothership::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
}

void AGFTMothership::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("GameSpace")))
	{
		Destroy();
	}
}