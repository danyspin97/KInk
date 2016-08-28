// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "SeaStar.h"

void ASeaStar::Fire(const FVector& PlayerLocation)
{
	for (int32 i = 0; i < NumberOfBullet; ++i)
	{
		const FVector& Location = GetCapsuleComponent()->GetComponentLocation();
		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(Location, PlayerLocation);
		const FVector& Direction = FRotationMatrix(FRotator(Rotation.Pitch, Rotation.Yaw - 10, Rotation.Roll)).GetUnitAxis(EAxis::X);
		PoolRef->PoolProjectile(GetWorld(), Projectile, this->GetClass(), Location, Rotation, Direction, (float)BulletDamage * GameState->Multiplier);
	}
}

