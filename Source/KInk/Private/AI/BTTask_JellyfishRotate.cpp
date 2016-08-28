// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "AI/BaseBotController.h"
#include "BTTask_JellyfishRotate.h"
#include "Enemy/Enemy.h"

EBTNodeResult::Type UBTTask_JellyfishRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}
	
	FRotator NewRot = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Rotator>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("NewRot")));
	const FRotator& PawnRotation = Controller->EnemyPawn->GetCapsuleComponent()->GetComponentRotation();

	/*if (NewRot != PawnRotation)
	{
		//float LerpTime = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Float>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("LerpTime")));
		// Create a rotator using Value
		const FRotator Rotation(0, 2, 0);
		// Rotate the ship by rotating the capsule component, that have all the mesh attached to it
		Controller->GetEnemyPawn()->GetCapsuleComponent()->AddRelativeRotation(Rotation);
		//Set Rot
		return EBTNodeResult::InProgress;
	}*/
	return EBTNodeResult::Succeeded;


	
}

