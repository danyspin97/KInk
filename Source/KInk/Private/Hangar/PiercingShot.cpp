// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "World/Pooling.h"
#include "Player/Kraken.h"
#include "Kismet/KismetMathLibrary.h"
#include "Hangar/PiercingProjectile.h"
#include "PaperFlipbookComponent.h"
#include "StaticLibrary.h"
#include "PiercingShot.h"

APiercingShot::APiercingShot()
{
	Weapon = EWeapon::WPiercingShot;
}

void APiercingShot::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentWeaponType = EWeapon::WPiercingShot;
}

void APiercingShot::DeactivatePowerUp()
{
	auto CustomPlayerState = Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	CustomPlayerState->CurrentWeaponType = EWeapon::WFireGun;
	CustomPlayerState->CurrentWeaponPowerUp = nullptr;
	K2_DestroyActor();
}

