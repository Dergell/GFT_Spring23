// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFT_Spring23/Interfaces/GFTImpactable.h"
#include "GFTInvader.generated.h"

class UBoxComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInvaderLeavingVolume, AActor*, Invader, AActor*, Volume);

UCLASS()
class GFT_SPRING23_API AGFTInvader : public AActor, public IGFTImpactable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTInvader();

protected:
	virtual void BeginPlay() override;

public:
	// React to a ball impact
	virtual void BallImpact_Implementation() override;

	// Callback for whenever we leave an overlap
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Broadcast when leaving a volume with tag "InvaderSpace"
	UPROPERTY(BlueprintAssignable)
	FOnInvaderLeavingVolume OnInvaderLeavingVolume;

private:
	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// How many points this invader is worth once destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Points = 100;
};