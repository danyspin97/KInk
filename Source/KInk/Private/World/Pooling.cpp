// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "ArcadeGameMode.h"
#include "Enemy.h"
#include "Kraken.h"
#include "Projectile.h"
#include "StaticLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "Pooling.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

#define MAXENEMIES 15
#define MAXPROJECTILES 25

// Sets default values
APooling::APooling()
{
	PrimaryActorTick.bCanEverTick = false;
	bPoolActive = false;
}

// Called when the game starts or when spawned
void APooling::BeginPlay()
{
	Super::BeginPlay();
	bPoolActive = false;
	
}

// Called every frame
void APooling::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void APooling::InitPool()
{
	EnemyArray.Empty();
	ProjectileArray.Empty();
	for (int32 i = 0; i < Enemies.Num(); i++)
	{
		int32 k = EnemyArray.Add(FEnemyPooling(Enemies[i]));
		for (int32 l = 0; l < MAXENEMIES; l++)
		{
			AEnemy* NewEnemy = UStaticLibrary::SpawnBP<AEnemy>(GetWorld(), Enemies[i], DeactivateLocation, FRotator());
			if (NewEnemy)
			{
				NewEnemy->SetActorEnableCollision(false);
				NewEnemy->SetActorTickEnabled(false);
				NewEnemy->GetCapsuleComponent()->SetWorldLocation(DeactivateLocation);
				NewEnemy->Deactivate();
				if (NewEnemy->Controller == NULL)
				{
					NewEnemy->SpawnDefaultController();
				}
				if (EnemyArray.IsValidIndex(k))
				{
					EnemyArray[k].DeactivatedEnemy.Add(NewEnemy);
				}
			}
		}
	}
	for (int32 i = 0; i < Projectiles.Num(); i++)
	{
		int32 k = ProjectileArray.Add(FProjectilePooling(Projectiles[i]));
		for (int32 l = 0; l < MAXPROJECTILES; l++)
		{
			AProjectile* NewProjectile = UStaticLibrary::SpawnBP<AProjectile>(GetWorld(), Projectiles[i], DeactivateLocation, FRotator());
			if (NewProjectile)
			{
				ProjectileArray[k].DeactivatedProjectile.Add(NewProjectile);
				NewProjectile->SetActorEnableCollision(false);
				NewProjectile->SetActorTickEnabled(false);
				NewProjectile->Deactivate();
			}
		}
	}
	for (int32 i = 0; i < Projectiles.Num(); i++)
	{
		for (int32 l = 0; l < ProjectileArray[i].DeactivatedProjectile.Num(); l++)
		{
			if (!ProjectileArray[i].DeactivatedProjectile.IsValidIndex(l) && !ProjectileArray[i].DeactivatedProjectile[l])
			{
				ProjectileArray[i].DeactivatedProjectile.RemoveAtSwap(l);
			}
		}
	}
	bPoolActive = true;
}

AEnemy* APooling::PoolEnemy(UWorld* World, UClass* EnemyClass, const FVector& Location, const FRotator& Rotation)
{
	for (int i = 0; i < EnemyArray.Num(); i++)
	{
		if (EnemyArray[i].EnemyClass == EnemyClass)
		{
			int32 DeactiveEnemyCont = 0;
			while ((DeactiveEnemyCont < EnemyArray[i].DeactivatedEnemy.Num()) && (!(EnemyArray[i].DeactivatedEnemy.IsValidIndex(DeactiveEnemyCont))))
			{
				DeactiveEnemyCont++;
			}
			if (EnemyArray[i].DeactivatedEnemy.IsValidIndex(DeactiveEnemyCont))
			{
				AEnemy* EnemyToPool = EnemyArray[i].DeactivatedEnemy[DeactiveEnemyCont];
				EnemyArray[i].DeactivatedEnemy.RemoveAtSwap(DeactiveEnemyCont);
				EnemyToPool->SetActorEnableCollision(true);
				EnemyToPool->SetActorHiddenInGame(false);
				EnemyToPool->SetActorTickEnabled(true);
				EnemyToPool->SetActorLocationAndRotation(Location, Rotation);
				EnemyToPool->GetCapsuleComponent()->SetWorldLocationAndRotation(Location, Rotation);
				EnemyToPool->Pool();
				return EnemyToPool;
			}
		}
	}
	return nullptr;
}

void APooling::DeactivateEnemy(AEnemy* EnemyToDeactivate)
{
	for (int i = 0; i < EnemyArray.Num(); i++)
	{
		if (EnemyArray[i].EnemyClass == EnemyToDeactivate->GetClass())
		{
			EnemyArray[i].DeactivatedEnemy.Add(EnemyToDeactivate);
			EnemyToDeactivate->SetActorEnableCollision(false);
			EnemyToDeactivate->SetActorTickEnabled(false);
			EnemyToDeactivate->Deactivate();
			EnemyToDeactivate->GetCapsuleComponent()->SetWorldLocation(DeactivateLocation);
			return;
		}
	}
}

AProjectile* APooling::PoolProjectile(UWorld* World, UClass* ProjectileClass, UClass* OwnerClass, const FVector& Location, const FRotator& Rotation, const FVector& Direction, int16 Damage, bool bIsCharacterOwning)
{
	for (int32 i = 0; i < ProjectileArray.Num(); i++)
	{
		if (ProjectileArray[i].ProjectileClass == ProjectileClass)
		{
			int32 k = 0;
			while ((k < ProjectileArray[i].DeactivatedProjectile.Num()) && !(ProjectileArray[i].DeactivatedProjectile.IsValidIndex(k)))
			{
				k++;
			}
			if (ProjectileArray[i].DeactivatedProjectile.IsValidIndex(k))
			{
				AProjectile* PoolProjectile = ProjectileArray[i].DeactivatedProjectile.Pop();
				PoolProjectile->SetActorEnableCollision(true);
				//PoolProjectile->SetActorLocationAndRotation(Location, Rotation);
				PoolProjectile->BoxComp->SetWorldLocationAndRotation(Location, Rotation);
				PoolProjectile->Pool(OwnerClass, Direction, Damage, bIsCharacterOwning);
				PoolProjectile->SetActorHiddenInGame(false);
				PoolProjectile->SetActorTickEnabled(true);
				return PoolProjectile;
			}
			/*else
			{
				AProjectile* NewProjectile = UStaticLibrary::SpawnBP<AProjectile>(World, ProjectileClass, Location + FVector(5000), Rotation);
				NewProjectile->Pool(OwnerClass, Direction, Damage, bIsCharacterOwning);
				NewProjectile->SetActorLocationAndRotation(Location, Rotation);
				return NewProjectile;
				if (NewProjectile)
				{
					return NewProjectile;
				}
				else
				{
					return NULL;
				}
			}*/
		}
	}
	return NULL;
}

void APooling::DeactivateProjectile(AProjectile* ProjectileToDeactivate)
{
	for (int32 i = 0; i < ProjectileArray.Num(); i++)
	{
		if (ProjectileArray[i].ProjectileClass == ProjectileToDeactivate->GetClass())
		{
			ProjectileArray[i].DeactivatedProjectile.Add(ProjectileToDeactivate);
			ProjectileToDeactivate->SetActorEnableCollision(false);
			ProjectileToDeactivate->SetActorTickEnabled(false);
			ProjectileToDeactivate->SetActorHiddenInGame(true);
			ProjectileToDeactivate->BoxComp->SetWorldLocation(DeactivateLocation);
			return;
		}
	}
}

void APooling::ClearPooling()
{
	for (TActorIterator<AEnemy> Enemies(GetWorld()); Enemies; ++Enemies)
	{
		DeactivateEnemy(*Enemies);
	}
	for (TActorIterator<AProjectile> Projectiles(GetWorld()); Projectiles; ++Projectiles)
	{
		DeactivateProjectile(*Projectiles);
	}
}