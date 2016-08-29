// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Heal.h"


AHeal::AHeal()
{
	Weapon = EWeapon::WFireGun;
}

void AHeal::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentHealth += LifeRestored;
	if (Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentHealth > Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->MaxHealth)
	{
		Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->CurrentHealth = Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState)->MaxHealth;
	}
}

void AHeal::DeactivatePowerUp()
{
	K2_DestroyActor();
}

