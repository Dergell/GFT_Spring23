// Brick Invaders - Copyright (C) 2023 Tony Schmich

#pragma once

#include "CoreMinimal.h"
#include "GFTEnemy.h"
#include "GFTInvader.generated.h"

class UArrowComponent;
class AGFTProjectile;

/**
 * Class represents an individual invader, moving with other invaders towards the player, occasionally shooting.
 * Movement and spawning is handled by GFTInvaderManager.
 */
UCLASS(Blueprintable)
class GFT_SPRING23_API AGFTInvader : public AGFTEnemy
{
	GENERATED_BODY()

public:
	AGFTInvader();

	// Returns true if no other Invader would block an attack
	bool HasClearShot();

	// Spawn a projectile at the Muzzle and send it away
	void Shoot();

private:
	// Arrow used as starting position of projectiles
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Muzzle;

	// Blueprint class to use when spawning a Ball
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<AGFTProjectile> ProjectileClass;

	// Sound played when shooting
	UPROPERTY(EditDefaultsOnly, Category=GFT, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundWave> ShootSound;
};