// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "AI/BaseBotController.h"
#include "Enemy/Enemy.h"
#include "BTTask_MoveJellyfish.h"

EBTNodeResult::Type UBTTask_MoveJellyfish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	auto pawn = Cast<AEnemy>(Controller->GetPawn());

	if (!pawn)
	{
		return EBTNodeResult::Failed;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//Controller->GetEnemyPawn()->AddMovementInput(Direction, 2);

	return EBTNodeResult::Succeeded;
}

