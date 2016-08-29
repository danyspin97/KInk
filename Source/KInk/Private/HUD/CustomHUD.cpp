// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "HUD/MainMenuWidget.h"
#include "HUD/PauseWidget.h"
#include "HUD/GameWidget.h"
#include "Player/BasePlayerController.h"
#include "HUD/BaseWidget.h"
#include "Player/Kraken.h"
#include "World/ArcadeGameState.h"
#include "CustomHUD.h"

void ACustomHUD::BeginPlay()
{
	FTimerHandle ScreenSizeTimerHandle;
	GetWorldTimerManager().SetTimer(ScreenSizeTimerHandle, this, &ACustomHUD::GetScreenSize, 0.2, false, -1.f);
}

void ACustomHUD::SetVisibleMainMenu()
{
	for (TObjectIterator<UBaseWidget> Widgets; Widgets; ++Widgets)
	{
		Widgets->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		if (!MainMenuWidget->IsInViewport())
		{
			MainMenuWidget->AddToViewport(0);
		}
	}
	else
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetBlueprint);
		MainMenuWidget->Initialize();
		MainMenuWidget->AddToViewport(0);
	}
}

void ACustomHUD::SetVisibleGameWidget()
{
	for (TObjectIterator<UBaseWidget> Widgets; Widgets; ++Widgets)
	{
		Widgets->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (PauseWidget)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
		if (!PauseWidget->IsInViewport())
		{
			PauseWidget->AddToViewport(0);
		}
	}
	else
	{
		PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetBlueprint);
		PauseWidget->Initialize();
		PauseWidget->AddToViewport(0);
		PauseWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (GameWidget)
	{
		GameWidget->SetVisibility(ESlateVisibility::Visible);
		if (!GameWidget->IsInViewport())
		{
			GameWidget->AddToViewport(0);
		}
	}
	else
	{
		GameWidget = CreateWidget<UGameWidget>(GetWorld(), GameWidgetBlueprint);
		GameWidget->Initialize();
		GameWidget->AddToViewport(0);
	}
}

void ACustomHUD::SetVisiblePauseWidget()
{
	for (TObjectIterator<UGameWidget> Widgets; Widgets; ++Widgets)
	{
		Widgets->SetVisibility(ESlateVisibility::Collapsed);
	}
	TObjectIterator<UPauseWidget> PauseWidget;
	if (PauseWidget)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACustomHUD::SetInvisiblePauseWidget()
{
	for (TObjectIterator<UPauseWidget> Widgets; Widgets; ++Widgets)
	{
		Widgets->SetVisibility(ESlateVisibility::Collapsed);
	}
	TObjectIterator<UGameWidget> GameWidget;
	if (GameWidget)
	{
		GameWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
}

void ACustomHUD::GetScreenSize()
{
	ScreenSize = GetWorld()->GetGameViewport()->Viewport->GetSizeXY();
	RatioY = (float)ScreenSize.Y / (float)1000;
	RatioX = (float)ScreenSize.X / (float)1000;

}

void ACustomHUD::SetGameOver()
{
	for (TObjectIterator<UBaseWidget> Widgets; Widgets; ++Widgets)
	{
		Widgets->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (GameOverWidget)
	{
		GameOverWidget->SetVisibility(ESlateVisibility::Visible);
		if (!GameOverWidget->IsInViewport())
		{
			GameOverWidget->AddToViewport(0);
		}
	}
	else
	{
		GameOverWidget = CreateWidget<UBaseWidget>(GetWorld(), GameOverWidgetBlueprint);
		GameOverWidget->Initialize();
		GameOverWidget->AddToViewport(0);
	}
}