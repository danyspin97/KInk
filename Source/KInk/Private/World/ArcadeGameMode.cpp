// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "World/ArcadeGameState.h"
#include "World/Pooling.h"
#include "Enemy.h"
#include "World/MessageHandler.h"
#include "Kraken.h"
#include "CustomHUD.h"
#include "StaticLibrary.h"
#include "Enemy/Enemy.h"
#include "Hangar/Projectile.h"
#include "Player/BasePlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "ArcadeGameMode.h"
#include "Player/CustomPlayerState.h"
#include "World/EnemySpawnerHandler.h"
#include "Hangar/PowerUp.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

AArcadeGameMode::AArcadeGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Soundtrack = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("Soundtrack"));
	Soundtrack->SetUISound(true);
}

void AArcadeGameMode::StartPlay()
{
	Super::StartPlay();
	Soundtrack->SetSound(MainMenuSoundtrack);
	Soundtrack->Play();
	Pool = UStaticLibrary::SpawnBP<APooling>(GetWorld(), PoolingBlueprint, FVector::FVector(0), FRotator::FRotator(0));
	Pool->InitPool();
	EnemySpawnerHandler = UStaticLibrary::SpawnBP<AEnemySpawnerHandler>(GetWorld(), EnemySpawnerHandlerBlueprint, FVector::FVector(0), FRotator::FRotator(0));
	MessageHandler = UStaticLibrary::SpawnBP<AMessageHandler>(GetWorld(), MessageHandlerBlueprint, FVector::FVector(0), FRotator::FRotator(0));
	GameState = Cast<AArcadeGameState>(GetWorld()->GetGameState());
	GameState->InGameState = EGameState::GS_InMainMenu;
	PlayerShip = Cast<AKraken>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GameHUD = Cast<ACustomHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	ThePC = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
}

void AArcadeGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameState->InGameState == EGameState::GS_InGame)
	{
		int32 i = 0;
		CameraLocation = PlayerShip->CameraComponent->GetComponentLocation();
		for (int32 i = 0; i < Pool->ProjectileArray.Num(); i++)
		{
			for (int32 j = 0; j < Pool->ProjectileArray[i].ActiveProjectile.Num(); j++)
			{
				if (Pool->ProjectileArray[i].ActiveProjectile[j] && !UStaticLibrary::IsInFrustum(Pool->ProjectileArray[i].ActiveProjectile[j], GetWorld()))
				{
					MessageData DestroyedData;
					DestroyedData.CauseDestroyed = ECauseDestroyed::ScreenLimit;
					// Say the message handler that the projectile has reached screen limit
					MessageHandler->ReceiveMessage(FMessage((AActor*)this, Pool->ProjectileArray[i].ActiveProjectile[j], EMessageData::Destroyed, DestroyedData));
				}
			}
		}
		if (GameState->bIsTextFading)
		{
			if (GameState->StringOpacity > 0.55)
			{
				GameState->StringOpacity = FMath::FInterpTo(GameState->StringOpacity, 0, DeltaTime, 0.2);
			}
			else
			{
				GameState->StringOpacity = FMath::FInterpTo(GameState->StringOpacity, 0, DeltaTime, 1.7);
				if (GameState->StringOpacity == 0.f)
				{
					GameState->bIsTextFading = false;
				}
			}			
		}
	}
}

void AArcadeGameMode::GameStart()
{
	if (!Pool->bPoolActive)
	{
		Pool->InitPool();
	}
	Soundtrack->SetSound(GameSoundtrack);
	GameState->Multiplier = 1.0f;
	GameState->InGameState = EGameState::GS_InGame;
	GameState->Wave = 1;
	GameState->DifficultyCounter = 0;
	PlayerShip->GameStart();
	EnemySpawnerHandler->GameStart();
	GetWorldTimerManager().SetTimer(IncreaseDifficultTimerHandle, this, &AArcadeGameMode::IncreaseDifficult, 20, true, -1.f);
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewport(true);
	ThePC->SetInputMode(InputMode);
}

void AArcadeGameMode::SpawnPowerUp(int32 Possibility, const FVector Location)
{	
	if (FMath::RandRange(0, 100) <= Possibility)
	{
		int32 PowerUpIndex = FMath::RandRange(0, PowerUps.Num() - 1);
		if (PowerUps.IsValidIndex(PowerUpIndex))
		{
			UStaticLibrary::SpawnBP<APowerUp>(GetWorld(), PowerUps[FMath::RandRange(0, PowerUps.Num() - 1)], Location, FRotator());
		}
	}
}

void AArcadeGameMode::IncreaseDifficult()
{
	GameState->Multiplier += 0.01f;
}

void AArcadeGameMode::PutScoreToBoard(FString Nickname, int32 Score)
{
	FScoreBoard NewScore = FScoreBoard(Nickname, Score);
	GameState->ScoreList.Add(NewScore);
	SortScoreList();
}

void AArcadeGameMode::SortScoreList()
{
	int8 ListCount = 0;
	int8 ListCount2 = 1;
	while (ListCount < GameState->ScoreList.Num() - 1)
	{
		ListCount2 = 1;
		while (ListCount2 < GameState->ScoreList.Num())
		{
			GameState->ScoreList[ListCount].MinorTo(GameState->ScoreList[ListCount2]);
			GameState->ScoreList.SwapMemory(ListCount, ListCount2);
			ListCount2++;
		}
		ListCount++;
	}
}

void AArcadeGameMode::GameOver()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	GetWorldTimerManager().ClearAllTimersForObject(EnemySpawnerHandler);
	Pool->ClearPooling();
	PlayerShip->SetActorTickEnabled(false);
	PlayerShip->GetController()->SetActorTickEnabled(false);
}