// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Player/Kraken.h"
#include "AI/BaseBotController.h"
#include "AI/BTService_CheckBotState.h"

/* AI Module includes */
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
/* This contains includes all key types like UBlackboardKeyType_Vector used below. */
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

void UBTService_CheckBotState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return;
	}
	const FVector& SelfLocation = Controller->GetSelfLocation();
	auto PlayerActor = Cast<AKraken>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerActor"))));
	if (!PlayerActor)
	{
		return;
	}
	const FVector& PawnLocation = PlayerActor->GetCapsuleComponent()->GetComponentLocation();
	int32 Dist = FVector::Dist(SelfLocation, PawnLocation);
	FBlackboard::FKey BotStateKey = OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("BotState"));
	FBlackboard::FKey PlayerLocationKey = OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerLocation"));
	EBotState BotState = static_cast<EBotState>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Enum>(BotStateKey));
	Controller->GetBlackboardComp()->SetValue<UBlackboardKeyType_Vector>(PlayerLocationKey, PawnLocation);
	if (Dist <= Controller->EnemyPawn->DistanceToAttack && BotState == EBotState::BT_Following)
	{
		EBotState NewBotState = EBotState::BT_Attacking;
		Controller->GetBlackboardComp()->SetValue<UBlackboardKeyType_Enum>(BotStateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(NewBotState));
	}
	else if (Dist > (Controller->EnemyPawn->DistanceToAttack + 20) && BotState == EBotState::BT_Attacking)
	{
		EBotState NewBotState = EBotState::BT_Following;
		Controller->GetBlackboardComp()->SetValue<UBlackboardKeyType_Enum>(BotStateKey, static_cast<UBlackboardKeyType_Enum::FDataType>(NewBotState));
	}
}


