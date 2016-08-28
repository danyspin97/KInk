// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "MoviePlayer.h"
#include "CustomGameInstance.h"

void UCustomGameInstance::Init()
{
	UGameInstance::Init();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UCustomGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UCustomGameInstance::EndLoadingScreen);
}

void UCustomGameInstance::BeginLoadingScreen()
{
	FLoadingScreenAttributes LoadingScreen;
	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
}

void UCustomGameInstance::EndLoadingScreen()
{

}

