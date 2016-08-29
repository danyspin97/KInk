// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/Actor.h"
#include "MessageHandler.generated.h"

UENUM()
enum class EMessageData : uint8
{
	Damage,
	Destroyed,
	PickedUp,
	ChangingGameState,
};

UENUM()
enum class ECauseDestroyed : uint8
{
	ScreenLimit,
	Projectile,
	ImpactWithShip,
	ExitGame,
};

UENUM()
enum class EGameStateChangeCause : uint8
{
	GameStarted,
	GamePaused,
	GameUnpaused,

};

// Struct used for send messages between actors(passing by class AMessageHandler)
struct FMessage
{
public:
	AActor* Sender;

	AActor* Destination;

	EMessageData TypeData;

	typedef union data MessageData;

	MessageData DataValue;
	
	FMessage(AActor* Sender, AActor* Destination, EMessageData TypeData, MessageData DataValue)
	{
		this->Sender = Sender;
		this->Destination = Destination;
		this->TypeData = TypeData;
		this->DataValue = DataValue;
	}
};

/*
 * Used for sending messages between actors:
 * actors use Message struct and fill it with info and data,
 * then they send it to this class that will forward it to the
 * destination actor after a check to content and respective updating of the stats.
 */
UCLASS()
class KINK_API AMessageHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMessageHandler();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Receive message
	void ReceiveMessage(FMessage Message);
	
	// Forward message to the destination
	void HandleMessage(FMessage Message);

	/*		REFERENCE TO GAME ACTORS		*/

	class ACustomPlayerState* PlayerState;

	class AMessageHandler* MessageHandler;

	class APooling* Pool;

	class AArcadeGameState* GameState;

	class AArcadeGameMode* GameMode;

	class AKraken* PlayerShip;

	class ABasePlayerController* ThePC;

	class ACustomHUD* GameHUD;
	
	class AEnemySpawnerHandler* EnemySpawnerHandler;

	// Init reference of actors created after BeginPlay
	void InitReference();

};
