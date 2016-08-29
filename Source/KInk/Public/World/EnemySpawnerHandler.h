// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawnerHandler.generated.h"

class AEnemy;

USTRUCT(Blueprintable)
struct FEnemySpawning
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
	//EEnemyType EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
	TSubclassOf<AEnemy> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
	float TimeToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawning")
	FVector2D SpawningLocation;

};

UCLASS()
class AEnemySpawnerHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnerHandler();

	virtual void BeginPlay() override;

	void GameStart();

	void SpawnNextEnemy();

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
		TArray<FEnemySpawning> EnemiesWave1;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
		TArray<FEnemySpawning> EnemiesWave2;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
		TArray<FEnemySpawning> EnemiesWave3;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
		TArray<FEnemySpawning> EnemiesWave4;

	FTimerHandle EnemySpawningTimerHandle;

	int32 EnemySpawned;

	int32 EnemyCont;

	FRotator DefaultEnemyRotation = FRotator(0, -180, 0);

	void SetWaveText();

	FString GetDifficultString(int32 DifficultyCounter);

	class AArcadeGameMode* GameMode;

	class AArcadeGameState* GameState;

	class APooling* Pool;

	void InitReference();

	void NextWave();

	void EnemyDestroyed() { EnemyCont--; if (EnemyCont == 0) NextWave(); };

};


