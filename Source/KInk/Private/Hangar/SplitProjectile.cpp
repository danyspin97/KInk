// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "World/Pooling.h"
#include "Kismet/KismetMathLibrary.h"
#include "Enemy/Enemy.h"
#include "World/MessageHandler.h"
#include "SplitProjectile.h"

void ASplitProjectile::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// If the projectile has been fired by the player and it impacts with the enemy
	if (OtherActor && bIsCharacterOwning && (OtherActor->IsA(AEnemy::StaticClass())))
	{
		FireSubProjectile(GetRenderComponent()->GetComponentLocation());
		MessageData DamageData;
		DamageData.Damage = Damage;
		TActorIterator<AMessageHandler> MessageHandler(GetWorld());
		// Say the message handler the this projectile damaged the impacted ship
		MessageHandler->ReceiveMessage(FMessage((AActor*)this, OtherActor, EMessageData::Damage, DamageData));
		MessageData DestroyedData;
		DestroyedData.CauseDestroyed = ECauseDestroyed::ImpactWithShip;
		// Destroy the projectile
		MessageHandler->ReceiveMessage(FMessage(OtherActor, (AActor*)this, EMessageData::Destroyed, DestroyedData));
	}
}

void ASplitProjectile::FireSubProjectile(FVector HitLocation)
{

	/*// The new rotation for the subsplitshot
	const FRotator Rotation1 = UKismetMathLibrary::FindLookAtRotation(HitLocation, FVector(HitLocation.X + 10, HitLocation.Y + 10, HitLocation.Z));
	const FRotator Rotation2 = UKismetMathLibrary::FindLookAtRotation(HitLocation, FVector(HitLocation.X + 10, HitLocation.Y - 10, HitLocation.Z));


	// Give Direction to these
	const FVector Direction1 = FRotationMatrix(Rotation1).GetUnitAxis(EAxis::X);
	const FVector Direction2 = FRotationMatrix(Rotation2).GetUnitAxis(EAxis::X);

	TActorIterator<APooling> Pool(GetWorld());
	Pool->PoolProjectile(GetWorld(), SubProjectileBlueprint, OwnerClass, HitLocation, Rotation1, BaseVelocity * 2, Direction1, Damage/2, Rate * 2, true);
	Pool->PoolProjectile(GetWorld(), SubProjectileBlueprint, OwnerClass, HitLocation, Rotation2, BaseVelocity * 2, Direction2, Damage/2, Rate * 2, true);*/
}

