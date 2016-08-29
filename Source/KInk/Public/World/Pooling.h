// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/Actor.h"
#include "Pooling.generated.h"

class AEnemy;
class AProjectile;

struct FEnemyPooling
{

	UClass* EnemyClass;

	typedef TArray<AEnemy*, TInlineAllocator<30>> PoolingEnemy;

	PoolingEnemy ActiveEnemy;
	PoolingEnemy DeactivatedEnemy;

	FEnemyPooling()
	{
		this->EnemyClass = NULL;
	}

	FEnemyPooling(UClass* EnemyClass)
	{
		this->EnemyClass = EnemyClass;
	}
};

struct FProjectilePooling
{
	UClass* ProjectileClass;

	UClass* OwnerClass;

	typedef TArray<AProjectile*, TInlineAllocator<70>> PoolingProjectile;

	PoolingProjectile DeactivatedProjectile;
	PoolingProjectile ActiveProjectile;

	FProjectilePooling()
	{

	}

	FProjectilePooling(UClass* ProjectileClass)
	{
		this->ProjectileClass = ProjectileClass;
		OwnerClass = nullptr;
	}

	FProjectilePooling(UClass* ProjectileClass, UClass* OwnerClass)
	{
		this->OwnerClass = OwnerClass;
		this->ProjectileClass = ProjectileClass;
	}
};

UCLASS()
class KINK_API APooling : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APooling();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Put all actor, except the player, in the pool
	FORCEINLINE void ClearPooling();

	// Get pool reference
	static APooling* GetPool();

	// Array of enemies stored in pool
	UPROPERTY(EditDefaultsOnly, Category = "Pooling")
	TArray<TSubclassOf<AEnemy>> Enemies;

	// Array of projectile stored in pool
	UPROPERTY(EditDefaultsOnly, Category = "Pooling")
	TArray<TSubclassOf<AProjectile>> Projectiles;

	// Take an enemy from the pool or spawn it if needed
	UFUNCTION(BlueprintCallable, Category = "Pooling")
	AEnemy* PoolEnemy(UWorld* World, UClass* EnemyClass, const FVector& Location, const FRotator& Rotation);

	// Deactivate and enemy putting it in the pool
	void DeactivateEnemy(class AEnemy* EnemyToDeactivate);

	// Take a projectile from the pool or spawn it if needed
	class AProjectile* PoolProjectile(UWorld* World, UClass* ProjectileClass, UClass* OwnerClass, const FVector& Location, const FRotator& Rotation, const FVector& Direction, int16 Damage, bool bIsCharacterOwning = false);

	// A projectile have hit something or went out of screen, move it in pool
	void DeactivateProjectile(class AProjectile* ProjectileToDeactivate);
	
	// Clear pool and then fill it
	void InitPool();

	bool bPoolActive = false;

	TArray<FEnemyPooling, TInlineAllocator<2>> EnemyArray;

	TArray<FProjectilePooling, TInlineAllocator<3>> ProjectileArray;

	FVector DeactivateLocation = FVector(50000, 50000, 0);
	
};


