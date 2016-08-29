// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "DoubleRate.h"

ADoubleRate::ADoubleRate()
{
	// The weapon is the default one
	Weapon = EWeapon::WFireGun;
}

void ADoubleRate::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Multiply the rate by the multiplier
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Rate *= Multiplier;
	// Recalculate the time between shots
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->FireRate = 1.0f / (Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Rate / 50);
}

void ADoubleRate::DeactivatePowerUp()
{
	// Divide the rate by the multiplier to put it back as it was
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Rate /= Multiplier;
	// Recalculate the time between shots
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->FireRate = 1.0f / (Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Rate / 50);
	// This power up has expired so we don't need it anymore
	K2_DestroyActor();
}


