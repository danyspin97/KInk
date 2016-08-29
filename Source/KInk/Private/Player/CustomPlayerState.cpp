// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "CustomPlayerState.h"

void ACustomPlayerState::ResetNewGame()
{
	CurrentHealth = MaxHealth;
	FireRate = 1.f / (Rate / 50.f);
	CurrentWeaponType = EWeapon::WFireGun;
	CurrentScore = 0;
	CurrentEnemyKilled = 0;
	bBigKraken = false;
}


