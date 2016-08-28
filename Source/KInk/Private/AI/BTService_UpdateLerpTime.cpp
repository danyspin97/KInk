// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "BTService_UpdateLerpTime.h"



void UBTService_UpdateLerpTime::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	float LerpTime = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Float>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("LerpTime")));
	LerpTime += DeltaSeconds;
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Float>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("LerpTime")), LerpTime);
}
