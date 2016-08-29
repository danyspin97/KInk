// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "BTTask_Fire.h"

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	pawn->Fire();

	return EBTNodeResult::Succeeded;
}


