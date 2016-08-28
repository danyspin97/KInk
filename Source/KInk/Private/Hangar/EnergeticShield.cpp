// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "EnergeticShield.h"

AEnergeticShield::AEnergeticShield()
{
	// The weapon is the default one
	Weapon = EWeapon::WFireGun;
}

void AEnergeticShield::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Set the life to the energetic shield of the player ship
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->ShieldLife = EnegerticShieldLife;
}

void AEnergeticShield::DeactivatePowerUp()
{
	// Destroy this power cause we have already updated the player stats increasing the shield life
	K2_DestroyActor();
}
