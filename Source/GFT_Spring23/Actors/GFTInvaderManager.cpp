// Fill out your copyright notice in the Description page of Project Settings.


#include "GFTInvaderManager.h"

#include "GFTInvader.h"
#include "Kismet/GameplayStatics.h"

AGFTInvaderManager::AGFTInvaderManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGFTInvaderManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Invaders;
	UGameplayStatics::GetAllActorsOfClass(this, AGFTInvader::StaticClass(), Invaders);
	for (AActor* InvaderActor : Invaders)
	{
		AGFTInvader* Invader = Cast<AGFTInvader>(InvaderActor);
		InvaderList.Add(Invader);
		Invader->OnActorBeginOverlap.AddDynamic(this, &AGFTInvaderManager::OnInvaderBeginOverlap);
		Invader->OnActorEndOverlap.AddDynamic(this, &AGFTInvaderManager::OnInvaderEndOverlap);
		Invader->OnDestroyed.AddDynamic(this, &AGFTInvaderManager::OnInvaderDestroyed);
	}
}

void AGFTInvaderManager::Initialize(FInvaderConfiguration InvaderConfig)
{
	MovementRate = InvaderConfig.MovementRate;
	FinalMovementRate = InvaderConfig.FinalMovementRate;
	MinAttackInterval = InvaderConfig.MinAttackInterval;
	MaxAttackInterval = InvaderConfig.MaxAttackInterval;
	MovementVector = FVector(100, 0, 0);

	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &AGFTInvaderManager::PerformMove, MovementRate);

	const float Interval = FMath::FRandRange(MinAttackInterval, MaxAttackInterval);
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AGFTInvaderManager::PerformAttack, Interval);
}

void AGFTInvaderManager::OnInvaderBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("BlockZ")))
	{
		bShouldMoveDown = false;
	}

	if (!bWasReverted && OtherActor->ActorHasTag(TEXT("BlockX")))
	{
		if (bShouldMoveDown)
		{
			MovementVector.Z = -100;
		}
		MovementVector.X *= -1;
		bWasReverted = true;
	}
}

void AGFTInvaderManager::OnInvaderEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!OtherActor->ActorHasTag(TEXT("BlockZ")))
	{
		return;
	}

	TArray<AActor*> OverlappingInvaders;
	OtherActor->GetOverlappingActors(OverlappingInvaders, AGFTInvader::StaticClass());
	if (OverlappingInvaders.IsEmpty())
	{
		bShouldMoveDown = true;
	}
}

void AGFTInvaderManager::OnInvaderDestroyed(AActor* DestroyedActor)
{
	const float Reduction = (MovementRate - FinalMovementRate) / InvaderList.Num();
	MovementRate -= Reduction;

	AGFTInvader* Invader = Cast<AGFTInvader>(DestroyedActor);
	InvaderList.Remove(Invader);
}

void AGFTInvaderManager::PerformMove()
{
	// Cache the currently used vector, since it will change while we move the invaders
	const FVector CurrentVector = MovementVector;
	// Reset Z movement, only required once
	MovementVector.Z = 0;

	for (AGFTInvader* Invader : InvaderList)
	{
		FVector Location = Invader->GetActorLocation();

		// Z movement has priority, only do X movement if no Z movement is required
		if (CurrentVector.Z != 0)
		{
			Location.Z += CurrentVector.Z;
		}
		else
		{
			Location.X += CurrentVector.X;
		}

		Invader->SetActorLocation(Location);
	}

	// Reset flag after each full cycle
	bWasReverted = false;

	// Set new timer for next movement here instead of looping, since MovementRate can change at any time
	GetWorld()->GetTimerManager().SetTimer(MovementTimer, this, &AGFTInvaderManager::PerformMove, MovementRate);
}

void AGFTInvaderManager::PerformAttack()
{
	// First we need to collect all invaders that have a clear shot
	TArray<AGFTInvader*> ReadyInvaders;
	for (AGFTInvader* Invader : InvaderList)
	{
		if (Invader->HasClearShot())
		{
			ReadyInvaders.Add(Invader);
		}
	}

	// Then we'll choose one of them for the attack
	const int32 Index = FMath::RandRange(0, ReadyInvaders.Num() - 1);
	ReadyInvaders[Index]->Shoot();

	// Finally we start the timer again
	const float Interval = FMath::FRandRange(MinAttackInterval, MaxAttackInterval);
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, this, &AGFTInvaderManager::PerformAttack, Interval);
}