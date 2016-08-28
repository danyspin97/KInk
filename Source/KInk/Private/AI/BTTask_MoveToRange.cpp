// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "BTTask_MoveToRange.h"
#include "AI/BaseBotController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Tasks/AITask_MoveTo.h"

EBTNodeResult::Type UBTTask_MoveToRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	FBTMoveToTaskMemory* MyMemory = (FBTMoveToTaskMemory*)NodeMemory;
	ABaseBotController* MyController = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	
	return NodeResult;
}
