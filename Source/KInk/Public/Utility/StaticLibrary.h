// Copyright (c) 2016 WiseDragonStd

#pragma once

//#include "BaseShip.h"
//#include "Projectile.h"

enum class ECauseDestroyed : uint8;

#include "StaticLibrary.generated.h"

/**
 * 
 */

typedef union data
{
	float Damage;
	// If the enemy has been destroyed the sender is who caused the damage, the destination is who has been destroyed
	ECauseDestroyed CauseDestroyed;

	// Puts gold and power up here 
	int32 Coin;

	class APowerUp* ActorPickedUp;
} MessageData;

UCLASS()
class UStaticLibrary : public UObject
{
	GENERATED_UCLASS_BODY()

		//FORCEINLNE function
		static FORCEINLINE bool IsValid(AActor* TheActor)
	{
		if (!TheActor) return false;
		if (!TheActor->IsValidLowLevel()) return false;
		return true;
	}

	static FORCEINLINE bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false
		) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Custom Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
			);

		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}

	template <typename CustomObjType>
	static FORCEINLINE CustomObjType* SpawnBP(
		UWorld* TheWorld,
		UClass* TheBP,
		const FVector& Loc,
		const FRotator& Rot,
		const bool bNoCollisionFail = true,
		AActor* Owner = NULL,
		APawn* Instigator = NULL
		){
		if (!TheWorld)
		{
			return NULL;
		}
		if (!TheBP)
		{
			return NULL;
		}
		//~~

		FActorSpawnParameters SpawnInfo;
		if (bNoCollisionFail)
		{
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		}
		else
		{
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		}
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.bDeferConstruction = false;

		return TheWorld->SpawnActor<CustomObjType>(TheBP, Loc, Rot, SpawnInfo);
	}

	// Is the actor in player screen? Check it using frustrum
	static bool IsInFrustum(AActor* Actor, UWorld* WorldContext);

	// Is the projectile on player screen?
	static bool IsInFrustum(class AProjectile* Projectile, UWorld* WorldContext);

	// Is the enemy on player screen?
	static bool IsInFrustum(class AEnemy* Enemy, UWorld* WorldContext);
};
