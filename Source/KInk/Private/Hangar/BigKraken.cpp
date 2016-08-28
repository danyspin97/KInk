// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Player/Kraken.h"
#include "Utility/EffectsActor.h"
#include "Utility/EvolutionEffect.h "
#include "BigKraken.h"

ABigKraken::ABigKraken()
{
	Weapon = EWeapon::WFireGun;
	BigKraken = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("BigKraken"));
	if (BigKraken)
	{
		BigKraken->bOnlyOwnerSee = true;
		BigKraken->bAffectDynamicIndirectLighting = false;
		BigKraken->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		BigKraken->SetCollisionProfileName(CollisionProfileName);
		BigKraken->bGenerateOverlapEvents = false;
		BigKraken->AttachTo(RootComponent);
	}
}

void ABigKraken::ActivatePowerUp()
{
	Super::ActivatePowerUp();
	auto CustomPlayerState = Cast<ACustomPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
	// Multiply the rate by the multiplier
	CustomPlayerState->bBigKraken = true;
	auto Kraken = Cast<AKraken>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// set the kraken direction
	Kraken->GetCapsuleComponent()->SetWorldRotation(FRotator(0, -180, 0));
	const FVector& ShipLocation = Kraken->GetCapsuleComponent()->GetComponentLocation();
	Kraken->GetSprite()->SetPlaybackPositionInFrames(0, false);
	AEvolutionEffect* EvolutionEffectRef = UStaticLibrary::SpawnBP<AEvolutionEffect>(GetWorld(), EvolutionEffect, FVector(ShipLocation.X, ShipLocation.Y, ShipLocation.Z + 1), FRotator());
	EvolutionEffectRef->PowerUp = this;
	GetWorld()->GetFirstPlayerController()->SetPause(true);
}

void ABigKraken::DeactivatePowerUp()
{
	AKraken* Kraken = Cast<AKraken>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Divide the ship damage by the multiplier to put it back as it was
	if (Kraken)
	{
		auto PlayerState = Cast<ACustomPlayerState>(Kraken->PlayerState);
		if (PlayerState)
		{
			PlayerState->bBigKraken = false;
		}
		Kraken->GetSprite()->SetFlipbook(Kraken->IdleAnim->GetFlipbook());
		Kraken->GetCapsuleComponent()->SetCapsuleSize(33, 33);
		Kraken->GetCharacterMovement()->MaxSpeed = DefaultSpeed;
	}
	// This power up has expired so we don't need it anymore
	K2_DestroyActor();
}

void ABigKraken::FinishedEvolutionAnim()
{
	auto Kraken = Cast<AKraken>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Kraken->GetSprite()->SetFlipbook(BigKraken->GetFlipbook());
	Kraken->GetCapsuleComponent()->SetCapsuleSize(65, 65);
	const FVector& Location = Kraken->GetCapsuleComponent()->GetComponentLocation();
	Kraken->GetCapsuleComponent()->SetWorldLocationAndRotation(FVector(Location.X, Location.Y, 24), FRotator(0, -180, 0));
	DefaultSpeed = Kraken->GetCharacterMovement()->MaxSpeed;
	Kraken->GetCharacterMovement()->MaxSpeed = BigKrakenSpeed;
}
