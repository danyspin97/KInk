// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Kraken.h"
#include "World/MessageHandler.h"
#include "PickableActor.h"

APickableActor::APickableActor(const FObjectInitializer& ObjectInitializer)
{
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	GetRenderComponent()->AttachTo(RootComponent, TEXT("RootComponent"));
	GetRenderComponent()->SetWorldRotation(FRotator(0, 180, -90));

	// Put Actor tick to true here and then transform render component to scale (0,3)
	PrimaryActorTick.bCanEverTick = true;

	//SetActorTickEnabled(true);
}

void APickableActor::BeginPlay()
{
	FTimerHandle DestroyActor;
	GetWorldTimerManager().SetTimer(DestroyActor, this, &APickableActor::K2_DestroyActor, 20);
}

void APickableActor::Tick(float DeltaSecond)
{
	TActorIterator<AKraken> PlayerShip(GetWorld());
	const FVector PlayerShipLocation = PlayerShip->GetCapsuleComponent()->GetComponentLocation();
	const FVector SpriteLocation = GetRenderComponent()->GetComponentLocation();
	if ((FMath::Abs((int16)SpriteLocation.X - (int16)PlayerShipLocation.X) < Range) && (FMath::Abs((int16)SpriteLocation.Y - (int16)PlayerShipLocation.Y) < Range))
	{
		MessageData DataPicked = GetData();
		auto pawn = Cast<AKraken>(GetWorld()->GetFirstPlayerController()->GetPawn());
		TActorIterator<AMessageHandler> MessageHandler(GetWorld());
		MessageHandler->ReceiveMessage(FMessage((AActor*)this, (AActor*)pawn, EMessageData::PickedUp, DataPicked));
	}
}

MessageData APickableActor::GetData()
{
	MessageData Data = MessageData();
	return Data;
}