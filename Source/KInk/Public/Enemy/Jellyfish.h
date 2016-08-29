// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Enemy/Enemy.h"
#include "Jellyfish.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API AJellyfish : public AEnemy
{
	GENERATED_BODY()
	
public:
	AJellyfish(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* AlternativeAnim;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* IdleAnim;

	virtual void BeginPlay() override;
};
