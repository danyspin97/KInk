// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION()
		virtual void BeginLoadingScreen();
	UFUNCTION()
		virtual void EndLoadingScreen();
	
	
	
};
