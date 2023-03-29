// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFTInvader.generated.h"

class UBoxComponent;

UCLASS()
class GFT_SPRING23_API AGFTInvader : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGFTInvader();

private:
	// Box used as RootComponent and for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Collision;

	// Mesh with disabled collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
};