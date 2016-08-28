// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void Fire(const FVector& PlayerLocation) override;
	
	
};
