// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_FireTimeCheck.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UBTService_FireTimeCheck : public UBTService
{
	GENERATED_BODY()

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
	
};
