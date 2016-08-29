// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/PowerUp.h"
#include "DoubleRate.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ADoubleRate : public APowerUp
{
	GENERATED_BODY()
	
public:
	ADoubleRate();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	float Multiplier;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;
};
