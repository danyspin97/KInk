// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Kraken.h"
#include "DoubleSpeed.h"

ADoubleSpeed::ADoubleSpeed()
{
	Weapon = EWeapon::WFireGun;
}

void ADoubleSpeed::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Get a reference to the pawn
	TActorIterator<AKraken> Ship(GetWorld());
	// Multiply the speed of the ship
	Ship->GetCharacterMovement()->MaxSpeed *= Multiplier;
}

void ADoubleSpeed::DeactivatePowerUp()
{
	TActorIterator<AKraken> Ship(GetWorld());
	// Divide the speed to put it back as it was
	Ship->GetCharacterMovement()->MaxSpeed /= Multiplier;
	// This power up has expired so we don't need it anymore
	K2_DestroyActor();
}
