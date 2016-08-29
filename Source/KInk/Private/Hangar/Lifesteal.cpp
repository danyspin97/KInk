// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Lifesteal.h"

ALifesteal::ALifesteal()
{
	Weapon = EWeapon::WFireGun;
}

void ALifesteal::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Lifesteal += LifestealAdded;
}

void ALifesteal::DeactivatePowerUp()
{
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->Lifesteal -= LifestealAdded;
	K2_DestroyActor();
}