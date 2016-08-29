// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Jellyfish.h"

AJellyfish::AJellyfish(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Try to create the AlternativeAnim component
	AlternativeAnim = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("AlternativeAnim"));
	if (AlternativeAnim)
	{
		AlternativeAnim->bOnlyOwnerSee = true;
		AlternativeAnim->bAffectDynamicIndirectLighting = true;
		AlternativeAnim->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		AlternativeAnim->AttachParent = GetCapsuleComponent();
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		AlternativeAnim->SetCollisionProfileName(CollisionProfileName);
		AlternativeAnim->bGenerateOverlapEvents = false;
		AlternativeAnim->AttachTo(GetCapsuleComponent());
	}
	IdleAnim = CreateOptionalDefaultSubobject<UPaperFlipbookComponent>(TEXT("IdleAnim"));
	if (IdleAnim)
	{
		IdleAnim->bOnlyOwnerSee = true;
		IdleAnim->bAffectDynamicIndirectLighting = false;
		IdleAnim->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		IdleAnim->AttachParent = GetCapsuleComponent();
		static FName CollisionProfileName(TEXT("CharacterMesh"));
		IdleAnim->SetCollisionProfileName(CollisionProfileName);
		IdleAnim->bGenerateOverlapEvents = false;
		IdleAnim->AttachTo(GetCapsuleComponent());
	}
}

void AJellyfish::BeginPlay()
{
	Super::BeginPlay();
	GetSprite()->SetFlipbook(IdleAnim->GetFlipbook());
}


