// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Enemy.h"
#include "BaseBotController.h"
#include "Pooling.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseBotController::ABaseBotController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

}

void ABaseBotController::BeginPlay()
{
	EnemyPawn = Cast<AEnemy>(this->GetPawn());
}

void ABaseBotController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AEnemy* ShipBot = Cast<AEnemy>(InPawn);
	if (ShipBot)
	{
		if (ShipBot->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*ShipBot->BehaviorTree->BlackboardAsset);

		}

		BehaviorComp->StartTree(*ShipBot->BehaviorTree);
		EnemyPawn = ShipBot;
	}
}

void ABaseBotController::UnPossess()
{
	Super::UnPossess();

	/* Stop any behavior running as we no longer have a pawn to control */
	BehaviorComp->StopTree();
}

void ABaseBotController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

FVector ABaseBotController::GetSelfLocation()
{
	return EnemyPawn->GetCapsuleComponent()->GetComponentLocation();
}

FVector ABaseBotController::GetForwardVector()
{
	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
	// get forward vector
	return FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
}

UFloatingPawnMovement* ABaseBotController::GetCharacterMovement()
{
	return EnemyPawn->GetCharacterMovement();
}

void ABaseBotController::StopBehaviorTree()
{
	BehaviorComp->StopTree();
}

void ABaseBotController::StartBehaviorTree()
{
	BehaviorComp->RestartTree();
}
