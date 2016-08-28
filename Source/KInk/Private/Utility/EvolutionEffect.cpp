// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "EvolutionEffect.h"

AEvolutionEffect::AEvolutionEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetRenderComponent()->SetTickableWhenPaused(true);
}

void AEvolutionEffect::FinishedPlaying()
{
	GetWorld()->GetFirstPlayerController()->SetPause(false);
	if (PowerUp)
	{
		PowerUp->FinishedEvolutionAnim();
	}
	Super::FinishedPlaying();
}


