// Fill out your copyright notice in the Description page of Project Settings.

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
	auto PlayerActor = Cast<AKraken>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerActor"))));
	if (!PlayerActor)
	{
		return EBTNodeResult::Failed;
	}
	const FVector& PlayerLocation = PlayerActor->GetCapsuleComponent()->GetComponentLocation();
	pawn->FireTimeCheck(PlayerLocation);

	return EBTNodeResult::Succeeded;
}


