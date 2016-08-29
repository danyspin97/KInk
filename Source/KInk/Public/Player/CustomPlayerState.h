// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/PlayerState.h"
#include "CustomPlayerState.generated.h"

enum class EWeapon : uint8;

/**
 * This class contains all stats about player games played and current game stats.
 * After "Game Over" the player stats are updated, adding enemies killed or setting new bestscore;
 * then all the ShipsStats gets resetetted.
 *
 */
UCLASS()
class KINK_API ACustomPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// Reset all Ship Stat for a new game, called by GameStart by the pawn
	void ResetNewGame();

	/**					SHIP STATS					**/
	/* 
	 * Ships stats are the stats that are used during a game.
	 * They contains health, power up value and score
	 */

	// The max health of the ship, set in the BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShipStats")
	int32 MaxHealth;

	// Current health of the ship, when it reaches 0 the game is over, it gets updated by the pawn class (AKraken)
	UPROPERTY(BlueprintReadWrite, Category = "ShipStats")
	int32 CurrentHealth;

	// The damage of the default weapon (Firegun), each projectile fired deals this value to enemies hit
	UPROPERTY(EditDefaultsOnly, Category = "ShipStats")
	int16 Damage;

	// The rate of the default weapon, 50 = 1 fire per second
	UPROPERTY(EditDefaultsOnly, Category = "ShipStats")
	float Rate;

	// This value gets updated by GameStart() called by the pawn and gets modified only when the ship weapon changes, it store the seconds that have to pass between each fire
	UPROPERTY()
	float FireRate;

	// This enum store the current weapon the ship is using (default is Firegun)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShipStats")
	EWeapon CurrentWeaponType;

	// Reference to the power up that changed the weapon type of the player
	class APowerUp* CurrentWeaponPowerUp;

	// Current percent of damage dealt to enemies that gets transformed in ship health. Ex: Player ship deals 100 damage to an enemy, Lifesteal% of damage dealt get added into health
	UPROPERTY()
	int16 Lifesteal;

	UPROPERTY()
	bool bBigKraken;

	// The amount of life that the shield has (Power Up Shield)
	UPROPERTY()
	int16 ShieldLife;

	// The value of the damage the ship body absorp (Power Up Absorbtion Body)
	UPROPERTY()
	int16 AbsorptionValue;

	UPROPERTY(BlueprintReadWrite, Category = "GameStats")
	int32 CurrentScore;

	UPROPERTY(BlueprintReadWrite, Category = "GameStats")
	int32 CurrentEnemyKilled;

	/**					PLAYER STATS					**/
	/*
	 * Player stats store all the value that persist between game and that are saved/load into the savegame
	 */

	// The amount of enemies killed by the player during all games
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 EnemiesKilled;
	
	// The amount of damage dealt during all games
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 DamageDealt;

	// The amount of damage taken by the player ship during all games
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 DamageTaken;

	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 HealthRestoredByLifesteal;

	// Total number of power ups picked up
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 PowerUpPickedUp;

	// Number of the games played
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 GamesPlayed;

	// Best score performed by the player
	UPROPERTY(BlueprintReadWrite, Category = "PlayerStats")
	int32 BestScore;
};
