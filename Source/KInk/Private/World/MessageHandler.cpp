// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Utility/StaticLibrary.h"
#include "World/MessageInterface.h"
#include "Enemy.h"
#include "Player/BasePlayerController.h"
#include "Player/CustomPlayerState.h"
#include "World/ArcadeGameMode.h"
#include "Kraken.h"
#include "MessageHandler.h"


// Sets default values
AMessageHandler::AMessageHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMessageHandler::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AArcadeGameMode>(GetWorld()->GetAuthGameMode());
	GameState = GetWorld()->GetGameState<AArcadeGameState>();
	ThePC = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerShip = Cast<AKraken>(ThePC->GetPawn());
	PlayerState = Cast<ACustomPlayerState>(PlayerShip->PlayerState);
	GameHUD = Cast<ACustomHUD>(ThePC->GetHUD());
	EnemySpawnerHandler = GameMode->EnemySpawnerHandler;
	FTimerHandle SetReferenceTimer;
	GetWorldTimerManager().SetTimer(SetReferenceTimer, this, &AMessageHandler::InitReference, 0.2);
}

void AMessageHandler::InitReference()
{
	MessageHandler = GameMode->MessageHandler;
	Pool = GameMode->Pool;
}

// Called every frame
void AMessageHandler::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void AMessageHandler::ReceiveMessage(FMessage Message)
{
	HandleMessage(Message);
}

void AMessageHandler::HandleMessage(FMessage Message)
{
	if (Message.Destination)
	{
		IMessageInterface* Interface = Cast<IMessageInterface>(Message.Destination);
		switch (Message.TypeData)
		{
		case EMessageData::Damage:
			if (Message.Destination->IsA(AEnemy::StaticClass()))
			{
				if (PlayerState->Lifesteal != 0)
				{
					int32 LifeRestored = Message.DataValue.Damage * PlayerState->Lifesteal / 100;
					PlayerState->CurrentHealth += LifeRestored;
					PlayerState->HealthRestoredByLifesteal += LifeRestored;
				}
				PlayerState->DamageDealt += Message.DataValue.Damage;
			}
			Interface->OnMessage(Message);
			break;
		case EMessageData::Destroyed:
			if (Message.Destination->IsA(AKraken::StaticClass()))
			{
				GameState->InGameState = EGameState::GS_InGameOver;
				GameHUD->SetGameOver();
				GameMode->GameOver();
				GetWorldTimerManager().ClearAllTimersForObject(GetWorld()->GetAuthGameMode());
				
				
			}
			switch (Message.DataValue.CauseDestroyed)
			{
			case ECauseDestroyed::Projectile:
				if (Message.Destination->IsA(AEnemy::StaticClass()))
				{
					auto Enemy = Cast<AEnemy>(Message.Destination);
					GameMode->SpawnPowerUp(Enemy->GetProbabilityOfPowerUp(), Enemy->GetCapsuleComponent()->GetComponentLocation());
					PlayerState->CurrentScore += Enemy->GetScoreGained() * GameState->Multiplier;
					EnemySpawnerHandler->EnemyDestroyed();
					PlayerState->EnemiesKilled++;
				}
				Interface->OnMessage(Message);
				break;
			case ECauseDestroyed::ImpactWithShip:
				if (Message.Destination->IsA(AEnemy::StaticClass()))
				{
					PlayerState->EnemiesKilled++;
					EnemySpawnerHandler->EnemyDestroyed();
				}
				Interface->OnMessage(Message);
			default:
				Interface->OnMessage(Message);
				break;
			}
			break;
		case EMessageData::PickedUp:
			if (Message.DataValue.ActorPickedUp)
			{
				PlayerState->PowerUpPickedUp++;
			}
			Interface->OnMessage(Message);
			break;
		default:
			break;
		}
	}
}