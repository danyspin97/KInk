// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "AI/BaseBotController.h"
#include "Enemy.h"
#include "SplineActor.h"
#include "Components/SplineComponent.h"
#include "BTTask_ResetEnemy.h"

#include "Player/BasePlayerController.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UBTTask_ResetEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Succeeded;
	}
	Controller->EnemyPawn->FireTimeCheck(FVector(0));
	
	return EBTNodeResult::Succeeded;
}

