// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickableActor.h"
#include "PowerUp.generated.h"

// Define how many weapons there are
#define WEAPONS 5

// Then set an index for each one
#define FIREGUN 0
#define PIERCINGSHOTS 1
#define SPLITSHOTS 2
#define BEAM 3
#define ROCKETS 4

/*
 * Put an enum for each weapon that can be used by the player
 */
UENUM(BlueprintType)
enum class EWeapon : uint8
{
	WFireGun = 0                UMETA(DisplayName = "FiregGun"),
	WPiercingShot = 1           UMETA(DisplayName = "PiercingShot"),
	WSplitShots = 2             UMETA(DisplayName = "SplitShots"),
	WBeam = 3                   UMETA(DisplayName = "Beam"),
	WRockets = 4                UMETA(DisplayName = "Rockets"),
};

/**
 * 
 */
UCLASS()
class KINK_API APowerUp : public APickableActor
{
	GENERATED_BODY()
public:

	// The time that the powerup stay active after the played pick it
	UPROPERTY(EditDefaultsOnly, Category = Attribute)
	int32 Time;

	float CurrentTime;

	EWeapon Weapon;
	
	bool UpdateTime(float DeltaTime);

	virtual void ActivatePowerUp();

	virtual void DeactivatePowerUp();

	virtual FORCEINLINE MessageData GetData() override;
};
