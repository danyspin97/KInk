// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Hangar/PowerUp.h"
#include "BigKraken.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ABigKraken : public APowerUp
{
	GENERATED_BODY()
	

public:
	ABigKraken();

	UPROPERTY(Category = Sprite, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* BigKraken;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	TSubclassOf<class AEvolutionEffect> EvolutionEffect;

	virtual void ActivatePowerUp() override;

	virtual void DeactivatePowerUp() override;

	void FinishedEvolutionAnim();
	
	UPROPERTY(EditDefaultsOnly, Category = PowerUp)
	int32 BigKrakenSpeed;
	
	int32 DefaultSpeed;
};
