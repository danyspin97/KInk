// Copyright (c) 2016 WiseDragonStd.

#include "KInk.h"
#include "StaticLibrary.h"
#include "KFishball.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

AKFishball::AKFishball(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FirstSocket = 0;
}

void AKFishball::Fire()
{
	if (!CanFire())
	{
		return;
	}
	Super::Fire();
	const FVector& SelfLocation = GetCapsuleComponent()->GetComponentLocation();
	int32 i = FirstSocket;
	while (i < NumberOfBullet)
	{
		FString ProjectileSocketName = FString(TEXT("Projectile"));
		ProjectileSocketName.AppendInt(i);
		const FVector& Location = GetSprite()->GetSocketLocation(FName(*ProjectileSocketName));
		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(Location, SelfLocation);
		const FVector& Direction = FRotationMatrix(FRotator(Rotation.Pitch, Rotation.Yaw + 180, Rotation.Roll)).GetUnitAxis(EAxis::X);
		PoolRef->PoolProjectile(GetWorld(), Projectile, this->GetClass(), Location, Rotation, Direction, (int16)((float)BulletDamage * GameState->Multiplier));
		i += 2;
	}
	if (FirstSocket == 0)
	{
		FirstSocket++;
	}
	else
	{
		FirstSocket = 0;
	}
}


