// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTMothership.generated.h"

class UBoxComponent;

UCLASS(NotPlaceable)
class GFT_SPRING23_API AGFTMothership : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTMothership();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Callback whenever we end an overlap
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	// Direction and speed of movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=GFT, meta=(AllowPrivateAccess = "true"))
	FVector Velocity;
};