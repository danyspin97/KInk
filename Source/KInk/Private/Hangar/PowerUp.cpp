// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Player/Kraken.h"
#include "PowerUp.h"

void APowerUp::ActivatePowerUp()
{
	SetActorLocation(FVector(5000));
	GetWorldTimerManager().ClearAllTimersForObject(this);
	FTimerHandle PowerUpDeactivation;
	GetWorldTimerManager().SetTimer(PowerUpDeactivation, this, &APowerUp::DeactivatePowerUp, Time);
}

void APowerUp::DeactivatePowerUp()
{

}

MessageData APowerUp::GetData()
{
	MessageData DataValue;
	DataValue.ActorPickedUp = this;
	return DataValue;
}