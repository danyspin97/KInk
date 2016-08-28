// Fill out your copyright notice in the Description page of Project Settings.

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

	virtual void Fire(const FVector& PlayerLocation) override;
	
	
};
