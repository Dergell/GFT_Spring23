// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTEnemy.h"

#include "Components/BoxComponent.h"
#include "GFT_Spring23/Interfaces/GFTGameFramework.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGFTEnemy::AGFTEnemy()
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

void AGFTEnemy::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentEndOverlap.AddDynamic(this, &AGFTEnemy::EndOverlap);
}

void AGFTEnemy::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("GameSpace")))
	{
		Destroy();
	}
}

void AGFTEnemy::BallImpact_Implementation()
{
	Destroy();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController != nullptr && PlayerController->Implements<UGFTGameFramework>())
	{
		IGFTGameFramework::Execute_ScoreUpdate(PlayerController, Points);
	}
}