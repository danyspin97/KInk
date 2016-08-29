// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Kraken.h"

#include "Engine.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "ConfigCacheIni.h"

#include "Pooling.h"
#include "Utility/StaticLibrary.h"
#include "Enemy.h"
#include "Hangar/Projectile.h"
#include "Player/BasePlayerController.h"
#include "CustomPlayerState.h"
#include "World/MessageHandler.h"
#include "PaperFlipbookComponent.h"
#include "World/ArcadeGameMode.h"
#include "World/ArcadeGameState.h"
#include "Projectile.h"

#include "Hangar/PiercingShot.h"

// Sets default values
AKraken::AKraken(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->SetCapsuleSize(33, 33);
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));
	CameraComponent->AttachTo(RootComponent);

	IdleAnim = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("IdleAnim"));
	if (IdleAnim)
	{
		IdleAnim->bAffectDynamicIndirectLighting = false;
		IdleAnim->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		IdleAnim->AttachParent = GetCapsuleComponent();
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		IdleAnim->SetCollisionProfileName(CollisionProfileName);
		IdleAnim->bGenerateOverlapEvents = false;
		IdleAnim->AttachTo(GetCapsuleComponent());
		IdleAnim->SetComponentTickEnabled(false);
	}

	InkFire = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("InkFire"));
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AKraken::OnHit);

	InkFire->VolumeMultiplier = 0;


	CapsuleHalfHeight = CapsuleComponent->GetScaledCapsuleHalfHeight() + 2;

}

// Called when the game starts or when spawned
void AKraken::BeginPlay()
{
	Super::BeginPlay();
	InitFireFunction();
	Sprite->SetHiddenInGame(true);
	CustomPlayerState = Cast<ACustomPlayerState>(PlayerState);
	GameMode = Cast<AArcadeGameMode>(GetWorld()->GetAuthGameMode());
	GameState = GetWorld()->GetGameState<AArcadeGameState>();
	FTimerHandle SetReferenceTimer;
	GetWorldTimerManager().SetTimer(SetReferenceTimer, this, &AKraken::InitReference, 0.2);
}

void AKraken::InitReference()
{
	MessageHandler = GameMode->MessageHandler;
	Pool = GameMode->Pool;
}

// Called every frame
void AKraken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector& CapsuleLocation = CapsuleComponent->GetComponentLocation();
	if (CapsuleLocation.Z != CapsuleHalfHeight && !CustomPlayerState->bBigKraken)
	{
		GetCapsuleComponent()->SetWorldLocation(FVector(CapsuleLocation.X, CapsuleLocation.Y, CapsuleHalfHeight));
	}
	CameraComponent->SetWorldLocation(FVector(GetCapsuleComponent()->GetComponentLocation().X, GetCapsuleComponent()->GetComponentLocation().Y, CameraComponent->GetComponentLocation().Z));
	// Add red color to sprite when hit and then fade it
	if (bDamaged)
	{
		ColorValue = FMath::FInterpTo(ColorValue, 1, DeltaTime, 0.5);
		Sprite->SetSpriteColor(FLinearColor(1, ColorValue, ColorValue));
		if (ColorValue == 0)
		{
			bDamaged = false;
		}
	}
}

void AKraken::GameStart()
{
	GetController()->SetActorTickEnabled(true);
	SetActorTickEnabled(true);
	// Set the sprite visible
	SetActorLocation(FVector(0));
	GetCapsuleComponent()->SetWorldLocation(FVector(0));
	Sprite->SetHiddenInGame(false);
	Sprite->SetSpriteColor(FLinearColor(1, 1, 1));
	CameraComponent->SetWorldLocation(FVector(0, 0, CameraComponent->GetComponentLocation().Z));
	FireTimeShip = 0;
	// Set the current stats of the ship to the default value
	CustomPlayerState->ResetNewGame();
	InkFire->VolumeMultiplier = 0.4;
}

void AKraken::GameOver()
{
	SetActorTickEnabled(false);
	GetController()->SetActorTickEnabled(false);
	Sprite->SetHiddenInGame(true);
}

void AKraken::MoveUp(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AKraken::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AKraken::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		// Is the other actor an enemy?
		if (OtherActor->IsA(AEnemy::StaticClass()) &&(((OtherActor == LastActorHit) && ((GetWorld()->GetTimeSeconds() - TimeLastHit) > 3)) || OtherActor != LastActorHit))
		{
			if (CanTakeDamage())
			{
				auto Enemy = Cast<AEnemy>(OtherActor);
				// Do the player get destroyed when impact with this enemy?
				// It does so set "Game Over"
				if (Enemy->bDestroyPlayerShipWhenImpact)
				{
					// The damage dealt to the enemy
					MessageData DamageData;
					DamageData.Damage = CustomPlayerState->Damage;
					// Say the message handler that the enemy has been damaged by impacting with the player
					MessageHandler->ReceiveMessage(FMessage(Cast<AActor>(this), OtherActor, EMessageData::Damage, DamageData));
					MessageData DestroyedData;
					DestroyedData.CauseDestroyed = ECauseDestroyed::ImpactWithShip;
					// Say the message handler that the player has being destroyed by impacting with an enemy
					MessageHandler->ReceiveMessage(FMessage(OtherActor, Cast<AActor>(this), EMessageData::Destroyed, DestroyedData));
					LastActorHit = OtherActor;
					TimeLastHit = GetWorld()->GetTimeSeconds();
				}
				// It doesn't so take damage for the player and destroy enemy
				else if (Enemy->bDealImpactDamage)
				{
					MessageData DamageData;
					// The damage dealt by the enemy
					DamageData.Damage = Enemy->GetImpactDamage();
					// Say the message handler that the player has been damaged
					MessageHandler->ReceiveMessage(FMessage(OtherActor, Cast<AActor>(this), EMessageData::Damage, DamageData));
					MessageData DamageData2;
					DamageData2.Damage = CustomPlayerState->Damage;
					// Say the message handler that the enemy has been damaged by impacting with the player
					MessageHandler->ReceiveMessage(FMessage(Cast<AActor>(this), OtherActor, EMessageData::Damage, DamageData2));
					LastActorHit = OtherActor;
					TimeLastHit = GetWorld()->GetTimeSeconds();
				}
			}
			else
			{
				auto Enemy = Cast<AEnemy>(OtherActor);
				// Get a reference to the message handler so we can pass it that this ship has impacted with an enemy or projectile
				MessageData DamageData;
				// The damage dealt by the enemy
				DamageData.Damage = 300;
				// Say the message handler that the player has been damaged
				MessageHandler->ReceiveMessage(FMessage((AActor*)this, OtherActor, EMessageData::Damage, DamageData));
			}
			
		}
	}
}

void AKraken::Fire(float DeltaSecond)
{
	if (GameState->InGameState == EGameState::GS_InGame)
	{
		FireTimeShip += DeltaSecond;
		// The integer value of the weapontype
		int32 WeaponIndex = static_cast<typename std::underlying_type<EWeapon>::type>(CustomPlayerState->CurrentWeaponType);
		// Check if enough time has passed to fire
		if ((FireTimeShip >= CustomPlayerState->FireRate) && (WeaponIndex < WEAPONS) && (WeaponIndex >= 0))
		{
			(this->* (FireFunctions[WeaponIndex]))();
			InkFire->Play();
			// Decrease FireTime
			FireTimeShip -= CustomPlayerState->FireRate;
		}
	}	
}

void AKraken::InitFireFunction()
{
	FireFunctions[FIREGUN] = &AKraken::FireFiregun;
	FireFunctions[PIERCINGSHOTS] = &AKraken::FirePiercingShot;
	FireFunctions[SPLITSHOTS] = &AKraken::FireSplitShot;
}

void AKraken::FireFiregun()
{
	// Give Direction to that
	const FVector& Direction = FRotationMatrix(FireRotation).GetUnitAxis(EAxis::Y);

	// Take each location from the sockets
	const FVector& Location = GetSprite()->GetSocketLocation("Projectile");

	// Fire
	Pool->PoolProjectile(GetWorld(), ProjectileBlueprint, this->GetClass(), Location, FireRotation, Direction, CustomPlayerState->Damage, true);


}

void AKraken::FirePiercingShot()
{
	// Fire
	const FRotator& Rotation = Controller->GetControlRotation();
	const FRotator& RotationForward = FRotator(0, Rotation.Yaw, 0);

	// Give Direction to that
	const FVector& Direction = FRotationMatrix(RotationForward).GetUnitAxis(EAxis::Y);

	const FVector& Location1 = GetSprite()->GetSocketLocation("Projectile1");
	const FVector& Location2 = GetSprite()->GetSocketLocation("Projectile2");


	//Pool->PoolProjectile(GetWorld(), PiercingProjectileBlueprint, GetClass()->GetName(), Location1, RotationForward, (int16)GetVelocity().X, Direction, (int16)PiercingShotsDamage, (int16)PiercingShotsRate, true);
	//Pool->PoolProjectile(GetWorld(), PiercingProjectileBlueprint,GetClass()->GetName(), Location2, RotationForward, (int16)GetVelocity().X, Direction, (int16)PiercingShotsDamage, (int16)PiercingShotsRate, true);
}

void AKraken::FireSplitShot()
{

}

float AKraken::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (CanTakeDamage())
	{
		// Decrease current health by damage
		if (CustomPlayerState->ShieldLife > 0)
		{
			CustomPlayerState->ShieldLife -= DamageAmount - CustomPlayerState->AbsorptionValue;
			if (CustomPlayerState->ShieldLife < 0)
			{
				CustomPlayerState->ShieldLife = 0;
			}
		}
		else
		{
			if (DamageAmount > 0)
			{
				// Decrease health by damage
				CustomPlayerState->CurrentHealth -= DamageAmount - CustomPlayerState->AbsorptionValue;
				// Stats increase
				CustomPlayerState->DamageTaken += DamageAmount - CustomPlayerState->AbsorptionValue;
				MessageData DestroyedData;
				if (CustomPlayerState->CurrentHealth <= 0)
				{
					CustomPlayerState->CurrentHealth = 0;
					if (DamageCauser)
					{
						if (DamageCauser->IsA(AProjectile::StaticClass()))
						{
							DestroyedData.CauseDestroyed = ECauseDestroyed::Projectile;
						}
						// Otherwise see if was a Ship(enemy inherit this class) that impacted
						else if (DamageCauser->IsA(ABaseShip::StaticClass()))
						{
							DestroyedData.CauseDestroyed = ECauseDestroyed::ImpactWithShip;
						}
					}
					else
						DestroyedData.CauseDestroyed = ECauseDestroyed::Projectile;
					// If a projectile caused the damage put the data to projectile

					if (MessageHandler)
					{
						// Tell the message handler that the ship has been destroyed and who destroyed it
						MessageHandler->ReceiveMessage(FMessage(DamageCauser, Cast<AActor>(this), EMessageData::Destroyed, DestroyedData));
					}
				}
				else if (CustomPlayerState->CurrentHealth > CustomPlayerState->MaxHealth)
				{
					CustomPlayerState->CurrentHealth = CustomPlayerState->MaxHealth;
				}
			}
			ColorValue = 0;
			bDamaged = true;
			return DamageAmount - CustomPlayerState->AbsorptionValue;
		}
	}
	
	return 0;
}

bool AKraken::CanTakeDamage()
{
	return !CustomPlayerState->bBigKraken;
}

void AKraken::OnMessage(struct FMessage Message)
{
	const FDamageEvent& DamageEvent = FDamageEvent();
	switch (Message.TypeData)
	{
	case EMessageData::Damage:
		UGameplayStatics::ApplyDamage(this, Message.DataValue.Damage, nullptr, Message.Sender, UDamageType::StaticClass());
		break;
	case EMessageData::Destroyed:
		switch (Message.DataValue.CauseDestroyed)
		{
		case ECauseDestroyed::Projectile:
		case ECauseDestroyed::ImpactWithShip:
			// Show "Game Over", Score
			// Save
			// Restart/Main Menu
			break;
		case ECauseDestroyed::ExitGame:
			// Save
			// Main Menu
			break;
		default:
			break;
		}
		break;
	// If the player picked up a power up
	case EMessageData::PickedUp:
		if (Message.DataValue.ActorPickedUp)
		{
			// If it is a power up that doesn't change ship weapon
			if (Message.DataValue.ActorPickedUp->Weapon != EWeapon::WFireGun)
			{
				// Check if the weapon isn't using the default weapon
				if (CustomPlayerState->CurrentWeaponType != EWeapon::WFireGun)
				{
					// That means that there is another power up that changes ship weapon, deactivate it
					if (CustomPlayerState->CurrentWeaponPowerUp)
					{
						CustomPlayerState->CurrentWeaponPowerUp->DeactivatePowerUp();
					}
				}
				// Now put the weapon power up reference to this new power up just picked
				CustomPlayerState->CurrentWeaponPowerUp = Message.DataValue.ActorPickedUp;
			}
			Message.DataValue.ActorPickedUp->ActivatePowerUp();
		}
		break;
	default:
		break;
	}
}