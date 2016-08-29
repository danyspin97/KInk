// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "PaperFlipbookComponent.h"
#include "EffectsActor.h"


AEffectsActor::AEffectsActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	GetRenderComponent()->AttachTo(RootComponent, TEXT("RootComponent"));
	GetRenderComponent()->SetWorldRotation(FRotator(0, 180, -90));
	GetRenderComponent()->SetLooping(false);
	GetRenderComponent()->OnFinishedPlaying.AddDynamic(this, &AEffectsActor::FinishedPlaying);
}

void AEffectsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEffectsActor::FinishedPlaying()
{
	K2_DestroyActor();
}
