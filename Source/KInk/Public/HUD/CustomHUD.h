// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ACustomHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void GetScreenSize();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HUD)
	FIntPoint ScreenSize;

	float RatioX;

	float RatioY;

	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetBlueprint;
	
	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<class UGameWidget> GameWidgetBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<class UPauseWidget> PauseWidgetBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf<class UBaseWidget> GameOverWidgetBlueprint;

	class UGameWidget* GameWidget;

	class UMainMenuWidget* MainMenuWidget;

	class UPauseWidget* PauseWidget;

	class UBaseWidget* GameOverWidget;
	
	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void SetVisibleMainMenu();

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void SetVisibleGameWidget();

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void SetVisiblePauseWidget();

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void SetInvisiblePauseWidget();

	UFUNCTION(BlueprintCallable, Category = HUDEvents)
	void SetGameOver();

};
