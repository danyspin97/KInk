// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Enemy.h"
#include "Kraken.h"
#include "Pooling.h"
#include "StaticLibrary.h"
#include "World/MessageHandler.h"
#include "PaperFlipbookComponent.h"
#include "PiercingProjectile.h"


void APiercingProjectile::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// If the projectile has been fired by the player and it impacts with the enemy
		if (bIsCharacterOwning && (OtherActor->IsA(AEnemy::StaticClass())))
		{
			MessageData DamageData;
			DamageData.Damage = Damage;
			TActorIterator<AMessageHandler> MessageHandler(GetWorld());
			// Say the message handler the this projectile damaged the impacted ship
			MessageHandler->ReceiveMessage(FMessage((AActor*)this, OtherActor, EMessageData::Damage, DamageData));
		}
	}
}


