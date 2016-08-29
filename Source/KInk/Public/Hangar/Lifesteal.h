// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/PowerUp.h"
#include "Lifesteal.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ALifesteal : public APowerUp
{
	GENERATED_BODY()
	
public:
	ALifesteal();

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
		int32 LifestealAdded;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;

	
	
};
