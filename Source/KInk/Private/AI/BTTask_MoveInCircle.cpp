// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "BTTask_MoveInCircle.h"

EBTNodeResult::Type UBTTask_MoveInCircle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	Controller->EnemyPawn->AddMovementInput(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(OwnerComp.GetBlackboardComponent()->GetKeyID("NextPoint")), 5);



	return EBTNodeResult::Succeeded;
}



