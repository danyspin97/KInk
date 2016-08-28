// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hangar/PowerUp.h"
#include "Beam.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ABeam : public APowerUp
{
	GENERATED_BODY()
	
public:
	ABeam();

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<class APiercingProjectile> BeamBlueprint;

	int32 Damage;

	int32 Rate;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;
	
	
	
};
