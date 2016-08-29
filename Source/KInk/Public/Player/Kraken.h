// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "BaseShip.h"
#include "PowerUp.h"
#include "World/MessageInterface.h"
#include "Kraken.generated.h"

UCLASS()
class KINK_API AKraken : public ABaseShip, public IMessageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKraken(const class FObjectInitializer& ObjectInitializer);

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitReference();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void GameStart();

	void GameOver();

	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	AActor* LastActorHit;

	float TimeLastHit;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	UAudioComponent* InkFire;

	// Called when the ship go up or down in ArcadeGameMode
	void MoveUp(float Value);

	// Called when the ship go right or left in ArcadeGameMode
	void MoveRight(float Value);

	float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	// This value store the time the last shot had been fired
	float FireTimeShip;

	FRotator FireRotation;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	TSubclassOf<class AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = SpawningBP)
	class UPaperFlipbookComponent* IdleAnim;
	
	// Contains the pointers to the function that fire
	typedef void (AKraken::*FireFunction) ();

	FireFunction FireFunctions[WEAPONS];

	/* Handle the fire and gets called each tick (passing the DeltaSeconds)
	 * @param WeaponIndex: index of the array of function that get called and that actually calculates Direction, Location and Rotation and fire the projectiles
	 */
	void Fire(float DeltaSecond);

	/*
	 * Init FireFunctions by passing it the reference to the functions
	 */
	void InitFireFunction();

	// Fire the basic weapon
	virtual void FireFiregun();

	// Fire piercing shot when the Power Up PiercingShot is active
	virtual void FirePiercingShot();

	// Fire splitshot then the Power Up SplitShot is active
	virtual void FireSplitShot();


	UPROPERTY(EditDefaultsOnly, Category = "PowerUp|PiercingShots")
	TSubclassOf<class APiercingProjectile> PiercingProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp|PiercingShots")
	int32 PiercingShotsDamage;

	UPROPERTY(EditDefaultsOnly, Category = "PowerUp|PiercingShots")
	int32 PiercingShotsRate;

	class ACustomPlayerState* CustomPlayerState;

	class AMessageHandler* MessageHandler;

	class APooling* Pool;

	class AArcadeGameState* GameState;

	class AArcadeGameMode* GameMode;

	FORCEINLINE bool CanTakeDamage();

	float CapsuleHalfHeight;

	bool bDamaged;

	float ColorValue;
public:
	// Handle a message from the message handler
	virtual void OnMessage(struct FMessage Message) override;

};
