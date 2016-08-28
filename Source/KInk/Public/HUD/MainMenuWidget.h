// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HUD/BaseWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UMainMenuWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = HUDEvents)
		void Play();
	
};
