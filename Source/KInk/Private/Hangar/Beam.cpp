// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "World/Pooling.h"
#include "Player/Kraken.h"
#include "Kismet/KismetMathLibrary.h"
#include "Hangar/PiercingProjectile.h"
#include "PaperFlipbookComponent.h"
#include "Beam.h"

ABeam::ABeam()
{
	// The weapon is the beam so set it for this power up
	Weapon = EWeapon::WBeam;
}

void ABeam::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	// Set the new weapon type of the ship as this weapon type (Beam)
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentWeaponType = Weapon;
}

void ABeam::DeactivatePowerUp()
{
	// Change it back to the default weapon
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentWeaponType = EWeapon::WFireGun;

}




