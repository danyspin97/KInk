// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/Projectile.h"
#include "SplitProjectile.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ASplitProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	virtual void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	// The reference to the projectile that will be fired everytime this main projectile hit an enemy
	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<class AProjectile> SubProjectileBlueprint;
	
	void FireSubProjectile(FVector HitLocation);
};
