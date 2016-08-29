// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/PowerUp.h"
#include "DoubleSpeed.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ADoubleSpeed : public APowerUp
{
	GENERATED_BODY()
	
public:
	ADoubleSpeed();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
		int32 Multiplier;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;

	
	
};
