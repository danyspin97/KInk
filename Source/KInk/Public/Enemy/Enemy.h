// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Player/BaseShip.h"
#include "World/MessageInterface.h"

enum class EBotState	: uint8;

#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AEnemy : public ABaseShip, public IMessageInterface
{
	GENERATED_BODY()

public:
	AEnemy(const class FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	virtual void FireTimeCheck(const FVector& PlayerLocation);

	virtual void Fire(const FVector& PlayerLocation);

	virtual void OnMessage(struct FMessage Message) override;

	FORCEINLINE class ABaseBotController* GetBotController() { return Cast<ABaseBotController>(GetController()); };

	UPROPERTY(EditDefaultsOnly, Category = Attack)
		int32 DistanceToAttack;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	TSubclassOf<class AEffectsActor> DestroyedEffect;

	// True if that ship destroy the player when it has been hit
	UPROPERTY(EditDefaultsOnly, Category = Attack)
		bool bDestroyPlayerShipWhenImpact;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
		bool bDealImpactDamage;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* SoundDestroyed;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
		UAudioComponent* AudioComponent;

	//UPROPERTY(EditDefaultsOnly, Category = Attack)
	//TSubclassOf<AProjectile> ProjectileBlueprint;

	//UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	//TArray<const FVector&> GetMultipleShotDirection();

	virtual void Pool();

	virtual void Deactivate();

	FORCEINLINE int32 GetMaxHealth() { return MaxHealth; };

	//FORCEINLINE void SetMaxHealth(int32 MaxHealth) { this->MaxHealth = MaxHealth; };

	FORCEINLINE int32 GetCurrentHealth() { return CurrentHealth; };

	FORCEINLINE void  SetCurrentHealth(int32 CurrentHealth) { this->CurrentHealth = CurrentHealth; };

	FORCEINLINE int32 GetBulletDamage() { return BulletDamage; };

	//FORCEINLINE void SetBulletDamage(int32 BulletDamage) { this->BulletDamage = BulletDamage; };

	FORCEINLINE int32 GetImpactDamage() { return ImpactDamage; };

	//FORCEINLINE void SetImpactDamage(int32 ImpactDamage) { this->ImpactDamage = ImpactDamage; };

	FORCEINLINE int32 GetProbabilityOfPowerUp() { return ProbabilityOfPowerUp; };

	FORCEINLINE int32 GetScoreGained() { return ScoreGained; };

	FORCEINLINE int32 GetRate() { return Rate; };

	float CapsuleHalfHeight;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 NumberOfBullet;

	float FireRate;

	float FireTime;

	class AMessageHandler* MessageHandler;

	class APooling* PoolRef;

	class AArcadeGameState* GameState;

	class AKraken* PlayerShip;
	
	void InitReference();

	float ColorValue;

	bool bDamaged;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 MaxHealth;

	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 Rate;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 ImpactDamage;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 BulletDamage;

	// Determine oh much probability there is to spawn a power up when this enemy is destroyed by the player
	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 ScoreGained;

	// Determine oh much probability there is to spawn a power up when this enemy is destroyed by the player
	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int32 ProbabilityOfPowerUp;

};
