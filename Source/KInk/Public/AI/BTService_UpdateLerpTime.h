// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateLerpTime.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UBTService_UpdateLerpTime : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
