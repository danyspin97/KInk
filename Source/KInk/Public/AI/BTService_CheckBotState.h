// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckBotState.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API UBTService_CheckBotState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
