// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Fishball.h"

void AFishball::Fire()
{
	Super::Fire();
	const FVector& SelfLocation = GetCapsuleComponent()->GetComponentLocation();
	for (int32 i = 0; i < NumberOfBullet; ++i)
	{
		FString ProjectileSocketName = FString(TEXT("Projectile"));
		ProjectileSocketName.AppendInt(i);
		const FVector& Location = GetSprite()->GetSocketLocation(FName(*ProjectileSocketName));
		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(Location, SelfLocation);
		const FVector& Direction = FRotationMatrix(FRotator(Rotation.Pitch, Rotation.Yaw - 20, Rotation.Roll)).GetUnitAxis(EAxis::X);
		PoolRef->PoolProjectile(GetWorld(), Projectile, this->GetClass(), Location, Rotation, Direction, (int16)((float)BulletDamage * GameState->Multiplier));
	}
}

