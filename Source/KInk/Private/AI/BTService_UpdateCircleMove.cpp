// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Player/Kraken.h"
#include "BTService_UpdateCircleMove.h"

void UBTService_UpdateCircleMove::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
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
	const FVector& PlayerLocation = PlayerActor->GetCapsuleComponent()->GetComponentLocation();

	int32 d = 500;
	FVector2D Delta;
	Delta.X = (int32)SelfLocation.X - (int32)PlayerLocation.X;
	Delta.Y = (int32)SelfLocation.Y - (int32)PlayerLocation.Y;
	int32 radius = FMath::Sqrt((int32)Delta.X*(int32)Delta.X + (int32)Delta.Y*(int32)Delta.Y);
	FVector2D Ortho;
	if (radius != 0)
	{
		Ortho.X = -(int32)Delta.Y*(int32)d / radius;
		Ortho.Y = (int32)Delta.X*(int32)d / radius;
		FVector2D NewDelta;
		NewDelta.X = (int32)Delta.X + (int32)Ortho.X;
		NewDelta.Y = (int32)Delta.Y + (int32)Ortho.Y;
		int32 newLength = FMath::Sqrt((int32)NewDelta.X*(int32)NewDelta.X + (int32)NewDelta.Y*(int32)NewDelta.Y);
		FVector2D A;
		if (newLength != 0)
		{
			A.X = (int32)PlayerLocation.X + (int32)NewDelta.X*radius / newLength;
			A.Y = (int32)PlayerLocation.Y + (int32)NewDelta.Y*radius / newLength;
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(OwnerComp.GetBlackboardComponent()->GetKeyID("NextPoint"), FVector(A, SelfLocation.Z));
		}
	}

	
}



