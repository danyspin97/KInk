// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "DoubleDamage.h"

ADoubleDamage::ADoubleDamage()
{
	// The weapon is the default one
	Weapon = EWeapon::WFireGun;
}

void ADoubleDamage::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Multiply the ship damage by the multiplier
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Damage *= Multiplier;
}

void ADoubleDamage::DeactivatePowerUp()
{
	// Divide the ship damage by the multiplier to put it back as it was
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Damage /= Multiplier;
	// This power up has expired so we don't need it anymore
	K2_DestroyActor();
}