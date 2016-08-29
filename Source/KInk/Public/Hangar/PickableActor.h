// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "PaperFlipbookActor.h"
#include "PickableActor.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API APickableActor : public APaperFlipbookActor
{
	GENERATED_BODY()
	
public:
	APickableActor(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSecond) override;
	
	UPROPERTY(EditDefaultsOnly, Category = Ship)
		int32 Range;

	typedef union data MessageData;

	virtual MessageData GetData();

};
