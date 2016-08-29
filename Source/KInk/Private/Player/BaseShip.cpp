// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "GameFramework/Character.h"
#include "Pooling.h"
#include "BaseShip.h"


// Sets default values
ABaseShip::ABaseShip(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CapsuleComponent"));
	if (CapsuleComponent)
	{
		CapsuleComponent->InitCapsuleSize(35.0f, 35.0f);
		CapsuleComponent->CanCharacterStepUpOn = ECB_No;
		CapsuleComponent->bShouldUpdatePhysicsVolume = true;
		CapsuleComponent->bCheckAsyncSceneOnMove = false;
		CapsuleComponent->bCanEverAffectNavigation = false;
		CapsuleComponent->bDynamicObstacle = false;
		RootComponent = CapsuleComponent;
	}


	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("Sprite"));
	if (Sprite)
	{
		Sprite->AlwaysLoadOnClient = true;
		Sprite->AlwaysLoadOnServer = true;
		Sprite->bOwnerNoSee = false;
		Sprite->bAffectDynamicIndirectLighting = true;
		Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Sprite->AttachParent = CapsuleComponent;
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		Sprite->SetCollisionProfileName(CollisionProfileName);
		Sprite->bGenerateOverlapEvents = false;
		Sprite->SetWorldRotation(FRotator(0, 0, -90));
	}
	
	PawnMovement = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("PawnMovement"));
	if (PawnMovement && CapsuleComponent)
	{
		PawnMovement->UpdatedComponent = CapsuleComponent;
	}

	bCanBeDamaged = true;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	NetPriority = 3.0f;

	BaseEyeHeight = 0.0f;
	bCollideWhenPlacing = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

// Called when the game starts or when spawned
void ABaseShip::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseShip::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	
}

void ABaseShip::StopMovement()
{
	GetCharacterMovement()->StopMovementImmediately();
}


