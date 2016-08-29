// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_UpdateCircleMove.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UBTService_UpdateCircleMove : public UBTService
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
	
};
