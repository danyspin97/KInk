// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Fire.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UBTTask_Fire : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
