// Copyright (c) 2016 WiseDragonStd.

#pragma once

#include "Enemy/Enemy.h"
#include "KFishball.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AKFishball : public AEnemy
{
	GENERATED_BODY()

public:
	AKFishball(const FObjectInitializer& ObjectInitializer);

	virtual void Fire() override;

	int FirstSocket;
	
};
