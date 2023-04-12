// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GFTPlayerState.generated.h"

/**
 * The player state is used to hold player status information, like score and lives.
 */
UCLASS()
class GFT_SPRING23_API AGFTPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Update the Score by adding Points
	void UpdateScore(int32 Points);

	// Getters
	int32 GetLives();

	// Setters
	void SetLives(int32 NewLives);

private:
	// Private Hudson: That's it, man. Game over, man. Game over!
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	int32 Lives = 3;
};