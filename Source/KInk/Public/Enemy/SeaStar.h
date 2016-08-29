// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Enemy/Enemy.h"
#include "SeaStar.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ASeaStar : public AEnemy
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void Fire(const FVector& Location) override;	
};
