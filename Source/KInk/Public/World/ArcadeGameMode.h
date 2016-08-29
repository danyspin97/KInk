// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/GameMode.h"
#include "ArcadeGameMode.generated.h"

//Forward declaration
class AEnemy;

class AEnemySpawnerHandler;

class APooling;

class AMessageHandler;

enum class EMessageData : uint8;

enum class EGameStateChangeCause : uint8;

/**
 * 
 */
UCLASS()
class KINK_API AArcadeGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AArcadeGameMode(const class FObjectInitializer& ObjectInitializer);
	
	virtual void StartPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void GameStart();

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<APooling> PoolingBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<AMessageHandler> MessageHandlerBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<AEnemySpawnerHandler> EnemySpawnerHandlerBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TArray<TSubclassOf<class APowerUp>> PowerUps;

	UPROPERTY(EditDefaultsOnly, Category = Soundtrack)
	class UAudioComponent* Soundtrack;

	UPROPERTY(EditDefaultsOnly, Category = Soundtrack)
	class USoundBase* MainMenuSoundtrack;

	UPROPERTY(EditDefaultsOnly, Category = Soundtrack)
	class USoundBase* GameSoundtrack;

	APooling* Pool;

	AMessageHandler* MessageHandler;

	AEnemySpawnerHandler* EnemySpawnerHandler;

	void SpawnEnemy();

	void IncreaseDifficult();
	
	// Handle the spawning of power ups, and it is called by MessageHandler
	void SpawnPowerUp(int32 Possibility, const FVector Location);

	FTimerHandle IncreaseDifficultTimerHandle;

	TArray<int32, TInlineAllocator<16>> XPointToSpawn;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void PutScoreToBoard(FString Nickname, int32 Score);

	void SortScoreList();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver();

	class AArcadeGameState* GameState;

	class ACustomHUD* GameHUD;

	class AKraken* PlayerShip;

	FVector CameraLocation;

	class ABasePlayerController* ThePC;

};
