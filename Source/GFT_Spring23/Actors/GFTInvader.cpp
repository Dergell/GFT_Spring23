// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvader.h"

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
}

void AGFTInvader::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentEndOverlap.AddDynamic(this, &AGFTInvader::OnEndOverlap);
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

void AGFTInvader::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("InvaderSpace")))
	{
		OnInvaderLeavingVolume.Broadcast(this, OtherActor);
	}
}