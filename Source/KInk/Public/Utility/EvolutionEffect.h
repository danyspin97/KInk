// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Utility/EffectsActor.h"
#include "EvolutionEffect.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AEvolutionEffect : public AEffectsActor
{
	GENERATED_BODY()
	
public:
	AEvolutionEffect(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	virtual void FinishedPlaying() override;
	
	class ABigKraken* PowerUp;
};
