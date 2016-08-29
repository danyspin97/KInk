// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Player/CustomPlayerState.h"
#include "AbsorptionShield.h"

AAbsorptionShield::AAbsorptionShield()
{
	// The weapon is the default one
	Weapon = EWeapon::WFireGun;
}

void AAbsorptionShield::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Change the value of the Absorption in the player state
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->AbsorptionValue += AbsorptionShieldValue;
}

void AAbsorptionShield::DeactivatePowerUp()
{
	// Reverse change to the value of the Absorption in the player state
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->AbsorptionValue -= AbsorptionShieldValue;
	K2_DestroyActor();
}

