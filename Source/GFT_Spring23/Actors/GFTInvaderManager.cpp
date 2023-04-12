// Brick Invaders - Copyright (C) 2023 Tony Schmich


#include "GFTInvaderManager.h"

#include "GFTBall.h"
#include "GFTInvader.h"
#include "GFT_Spring23/System/GFTGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGFTInvaderManager::AGFTInvaderManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGFTInvaderManager::Initialize(FInvaderConfiguration InvaderConfig)
{
	// First, collect all invaders in the level and add some delegates
	TArray<AActor*> Invaders;
	UGameplayStatics::GetAllActorsOfClass(this, AGFTInvader::StaticClass(), Invaders);
	for (AActor* InvaderActor : Invaders)
	{
		AGFTInvader* Invader = Cast<AGFTInvader>(InvaderActor);
		InvaderList.Add(Invader);

		Invader->OnActorBeginOverlap.AddDynamic(this, &AGFTInvaderManager::OnInvaderBeginOverlap);
		Invader->OnActorEndOverlap.AddDynamic(this, &AGFTInvaderManager::OnInvaderEndOverlap);
		Invader->OnEndPlay.AddDynamic(this, &AGFTInvaderManager::OnInvaderEndPlay);
	}

	// Then setup some basic states
	MovementRate = InvaderConfig.MovementRate;
	FinalMovementRate = InvaderConfig.FinalMovementRate;
	MinAttackInterval = InvaderConfig.MinAttackInterval;
	MaxAttackInterval = InvaderConfig.MaxAttackInterval;
	MoveSounds = InvaderConfig.MoveSounds;
	bWasReverted = false;
	bShouldMoveDown = true;
	MovementVector = FVector(100, 0, 0);

	// Now move the invaders down according to the current stage
	int32 Stage = GetGameInstance<UGFTGameInstance>()->GetStage();
	while (Stage > 1 && bShouldMoveDown)
	{
		for (AGFTInvader* Invader : InvaderList)
		{
			Invader->SetActorLocation(Invader->GetActorLocation() + FVector(0, 0, -100));
		}
		Stage--;
	}

	// Lastly, activate the timers
	const float Interval = FMath::FRandRange(MinAttackInterval, MaxAttackInterval);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AGFTInvaderManager::PerformAttack, Interval);
	GetWorldTimerManager().SetTimer(MovementTimer, this, &AGFTInvaderManager::PerformMove, MovementRate);
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

void AGFTInvaderManager::OnInvaderEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	const float Reduction = (MovementRate - FinalMovementRate) / InvaderList.Num();
	MovementRate -= Reduction;

	AGFTInvader* Invader = Cast<AGFTInvader>(Actor);
	InvaderList.Remove(Invader);

	if (InvaderList.IsEmpty())
	{
		GetWorldTimerManager().ClearTimer(AttackTimer);
		GetWorldTimerManager().ClearTimer(MovementTimer);
		OnStageClear.Broadcast();
	}
}

void AGFTInvaderManager::PerformMove()
{
	// Cache the currently used vector, since it will change while we move the invaders
	const FVector CurrentVector = MovementVector;
	// Reset Z movement, only required once
	MovementVector.Z = 0;

	// Do a reverse for loop, since Invaders might get destroyed during iteration
	for (int Index = InvaderList.Num() - 1; Index >= 0; --Index)
	{
		AGFTInvader* Invader = InvaderList[Index];

		FVector StartLocation = Invader->GetActorLocation();
		FVector EndLocation = StartLocation;

		// Z movement has priority, only do X movement if no Z movement is required
		if (CurrentVector.Z != 0)
		{
			EndLocation.Z += CurrentVector.Z;
		}
		else
		{
			EndLocation.X += CurrentVector.X;
		}

		// Sweeptest for the ball, so we don't just move over and block it without a hit
		FCollisionShape Shape = FCollisionShape::MakeBox(Invader->GetComponentsBoundingBox().GetExtent());
		FCollisionResponseParams Response;
		Response.CollisionResponse.SetAllChannels(ECR_Ignore);
		Response.CollisionResponse.SetResponse(ECC_GameTraceChannel1, ECR_Block);
		const bool Hit = GetWorld()->SweepTestByChannel(StartLocation, EndLocation, Invader->GetActorQuat(), ECC_GameTraceChannel1, Shape, FCollisionQueryParams::DefaultQueryParam, Response);
		if (Hit)
		{
			IGFTImpactable::Execute_BallImpact(Invader);
		}
		else
		{
			Invader->SetActorLocation(EndLocation);
		}
	}

	if (!MoveSounds.IsEmpty())
	{
		UGameplayStatics::PlaySound2D(this, MoveSounds[MoveSoundIndex]);
		MoveSoundIndex++;
		if (MoveSoundIndex >= MoveSounds.Num())
		{
			MoveSoundIndex = 0;
		}
	}

	// Reset flag after each full cycle
	bWasReverted = false;

	// Set new timer for next movement here instead of looping, since MovementRate can change at any time
	GetWorldTimerManager().SetTimer(MovementTimer, this, &AGFTInvaderManager::PerformMove, MovementRate);
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
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AGFTInvaderManager::PerformAttack, Interval);
}