// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Player/Kraken.h"
#include "AI/BaseBotController.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BTService_UpdatePlayerLocation.h"

void UBTService_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto PlayerActor = Cast<AKraken>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerActor"))));
	if (!PlayerActor)
	{
		return;
	}
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerLocation")), PlayerActor->GetCapsuleComponent()->GetComponentLocation());
}



