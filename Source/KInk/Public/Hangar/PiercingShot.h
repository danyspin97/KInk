// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hangar/PowerUp.h"
#include "PiercingShot.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API APiercingShot : public APowerUp
{
	GENERATED_BODY()
	
public:
	APiercingShot();

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;
};
