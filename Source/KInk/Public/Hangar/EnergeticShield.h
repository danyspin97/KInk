// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/PowerUp.h"
#include "EnergeticShield.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AEnergeticShield : public APowerUp
{
	GENERATED_BODY()	
public:
	AEnergeticShield();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	int32 EnegerticShieldLife;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;

};
