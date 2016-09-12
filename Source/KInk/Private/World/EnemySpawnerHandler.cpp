// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Enemy.h"
#include "World/ArcadeGameState.h"
#include "World/Pooling.h"
#include "EnemySpawnerHandler.h"

#define EASY "Easy"
#define NORMAL "Normal"
#define HARD "Hard"
#define INSANE "Insane"
#define HELL "KK: Kraken King"



// Sets default values
AEnemySpawnerHandler::AEnemySpawnerHandler()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawnerHandler::BeginPlay()
{
	Super::BeginPlay();
	GameState = Cast<AArcadeGameState>(GetWorld()->GetGameState());
	GameMode = Cast<AArcadeGameMode>(GetWorld()->GetAuthGameMode());
	FTimerHandle SetReferenceTimer;
	GetWorldTimerManager().SetTimer(SetReferenceTimer, this, &AEnemySpawnerHandler::InitReference, 0.2);
}

void AEnemySpawnerHandler::InitReference()
{
	Pool = GameMode->Pool;
}

void AEnemySpawnerHandler::GameStart()
{
	GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, 2, false);
	EnemySpawned = 0;
	EnemyCont = 0;
	SetWaveText();
}

void AEnemySpawnerHandler::NextWave()
{
	if (GameState->Wave < 4)
	{
		GameState->Wave++;
	}
	else
	{
		GameState->DifficultyCounter += 0.5;
		GameState->Wave = 1;
	}
	EnemySpawned = 0;
	EnemyCont = 0;
	GameState->Multiplier += 0.1;
	GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, 7, false);
	SetWaveText();
}

void AEnemySpawnerHandler::SpawnNextEnemy()
{
	FEnemySpawning* EnemySpawningInfo = nullptr;

	switch (GameState->Wave)
	{
	case 1:
		if (EnemySpawned < EnemiesWave1.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave1[EnemySpawned];
			GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, EnemiesWave1[EnemySpawned + 1].TimeToSpawn, false);
			EnemySpawned++;
			EnemyCont++;
		}
		else if (EnemySpawned == EnemiesWave1.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave1[EnemySpawned];
			EnemySpawned++;
			EnemyCont++;
		}
		break;
	case 2:
		if (EnemySpawned < EnemiesWave2.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave2[EnemySpawned];
			GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, EnemiesWave2[EnemySpawned + 1].TimeToSpawn, false);
			EnemySpawned++;
			EnemyCont++;
		}
		else if (EnemySpawned == EnemiesWave2.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave2[EnemySpawned];
			EnemySpawned++;
			EnemyCont++;
		}
		break;
	case 3:
		if (EnemySpawned < EnemiesWave3.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave3[EnemySpawned];
			GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, EnemiesWave3[EnemySpawned + 1].TimeToSpawn, false);
			EnemySpawned++;
			EnemyCont++;
		}
		else if (EnemySpawned == EnemiesWave3.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave3[EnemySpawned];
			EnemySpawned++;
			EnemyCont++;
		}
		break;
	case 4:
		if (EnemySpawned < EnemiesWave4.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave4[EnemySpawned];
			GetWorldTimerManager().SetTimer(EnemySpawningTimerHandle, this, &AEnemySpawnerHandler::SpawnNextEnemy, EnemiesWave4[EnemySpawned + 1].TimeToSpawn, false);
			EnemySpawned++;
			EnemyCont++;
		}
		else if (EnemySpawned == EnemiesWave4.Num() - 1)
		{
			EnemySpawningInfo = &EnemiesWave4[EnemySpawned];
			EnemySpawned++;
			EnemyCont++;
		}
		break;
	default:
		break;
		
	}
	const FVector& Location = FVector(FVector2D(GameMode->CameraLocation.X, GameMode->CameraLocation.Y) + EnemySpawningInfo->SpawningLocation, 0);
	const FRotator& Rotation = DefaultEnemyRotation;
	Pool->PoolEnemy(GetWorld(), EnemySpawningInfo->Enemy, Location, Rotation);

}

void AEnemySpawnerHandler::SetWaveText()
{
	GameState->EnemyWaveString = FString("Wave ") + FString::FromInt(GameState->Wave);
	GameState->DifficultString = GetDifficultString(GameState->DifficultyCounter);
	GameState->StringOpacity = 1;
	GameState->bIsTextFading = true;
}

FString AEnemySpawnerHandler::GetDifficultString(int32 DifficultyCounter)
{
	FString DifficultString;
	switch (DifficultyCounter)
	{
	case 0:
		DifficultString = EASY;
		break;
	case 1:
		DifficultString = NORMAL;
		break;
	case 2:
		DifficultString = HARD;
		break;
	case 3:
		DifficultString = INSANE;
		break;
	case 4:
		DifficultString = HELL;
		break;
	default:
		DifficultString = GetDifficultString(DifficultyCounter - 5) + FString("+");
		break;
	}
	return DifficultString;
}
