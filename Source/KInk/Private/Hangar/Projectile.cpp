// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Enemy.h"
#include "Kraken.h"
#include "Pooling.h"
#include "StaticLibrary.h"
#include "AI/SplineActor.h"
#include "World/MessageHandler.h"
#include "Components/SplineComponent.h"
#include "Projectile.h"
#include "PaperFlipbookComponent.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	BoxComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComp"));
	BoxComp->AttachTo(RootComponent);

	GetRenderComponent()->AttachTo(BoxComp);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	SetActorEnableCollision(true);

	CurrentVelocity = BaseVelocity;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector Location = GetRenderComponent()->GetComponentLocation();
	// Move that vector a little
	Location += Direction * CurrentVelocity * DeltaTime;
	// Set the vector as the new location of the player
	//SetActorLocation(Location);
	BoxComp->SetWorldLocation(Location);
	//SetActorLocation(Location);
}



void AProjectile::OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		// If the projectile has been fired by the player and it impacts with the enemy
		if (bIsCharacterOwning && (OtherActor->IsA(AEnemy::StaticClass())))
		{
			MessageData DamageData;
			DamageData.Damage = Damage;
			TActorIterator<AMessageHandler> MessageHandler(GetWorld());
			// Say the message handler the this projectile damaged the impacted ship
			MessageHandler->ReceiveMessage(FMessage((AActor*)this, OtherActor, EMessageData::Damage, DamageData));
			MessageData DestroyedData;
			DestroyedData.CauseDestroyed = ECauseDestroyed::ImpactWithShip;
			// Destroy the projectile
			MessageHandler->ReceiveMessage(FMessage(OtherActor, (AActor*)this, EMessageData::Destroyed, DestroyedData));
		}
		// If the projectile has been fired by an enemy and it impacts with the player
		else if (!bIsCharacterOwning && (OtherActor->IsA(AKraken::StaticClass())))
		{
			MessageData DamageData;
			DamageData.Damage = Damage;
			TActorIterator<AMessageHandler> MessageHandler(GetWorld());
			// Say the message handler the this projectile damaged the impacted ship
			MessageHandler->ReceiveMessage(FMessage((AActor*)this, OtherActor, EMessageData::Damage, DamageData));
			MessageData DestroyedData;
			DestroyedData.CauseDestroyed = ECauseDestroyed::ImpactWithShip;
			// Destroy the projectile
			MessageHandler->ReceiveMessage(FMessage(OtherActor, (AActor*)this, EMessageData::Destroyed, DestroyedData));
		}
	}
}

void AProjectile::Pool(UClass* OwnerClass, const FVector& Direction, int16 Damage, bool bIsCharacterOwning)
{
	this->OwnerClass = OwnerClass;
	this->Damage = Damage;
	this->bIsCharacterOwning = bIsCharacterOwning;
	this->Direction = Direction;
	CurrentVelocity = BaseVelocity;
}

void AProjectile::Deactivate()
{
	Direction = FVector();
	CurrentVelocity = 0;
}

void AProjectile::OnMessage(struct FMessage Message)
{
	if (Message.TypeData == EMessageData::Destroyed)
	{
		TActorIterator<APooling> Pool(GetWorld());
		Pool->DeactivateProjectile(this);
	}
}


