// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hangar/PowerUp.h"
#include "Heal.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AHeal : public APowerUp
{
	GENERATED_BODY()
	
public:
	AHeal();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
		int32 LifeRestored;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;

	
	
};
