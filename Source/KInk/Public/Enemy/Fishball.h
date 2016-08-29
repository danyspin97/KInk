// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Enemy/Enemy.h"
#include "Fishball.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AFishball : public AEnemy
{
	GENERATED_BODY()

	virtual void Fire() override;
	
	
};
