// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Enemy/Jellyfish.h"
#include "BTTask_FindNextPointJellyfish.h"
#include "Kismet/KismetMathLibrary.h"


EBTNodeResult::Type UBTTask_FindNextPointJellyfish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}
	auto PlayerActor = Cast<AKraken>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(OwnerComp.GetBlackboardComponent()->GetKeyID(TEXT("PlayerActor"))));
	if (!PlayerActor)
	{
		return EBTNodeResult::Failed;
	}
	const FVector& PlayerLocation = PlayerActor->GetCapsuleComponent()->GetComponentLocation();
	FVector RandomLocation;
	RandomLocation.X = FMath::FRandRange(PlayerLocation.X - 400, PlayerLocation.X + 400);
	RandomLocation.Y = FMath::FRandRange(PlayerLocation.Y - 320, PlayerLocation.Y + 320);

	if (Controller->GetPawn()->IsA(AJellyfish::StaticClass()))
	{
		Controller->EnemyPawn->GetCapsuleComponent()->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(Controller->EnemyPawn->GetCapsuleComponent()->GetComponentLocation(), RandomLocation));
	}

	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(OwnerComp.GetBlackboardComponent()->GetKeyID("NextPoint"), RandomLocation);
	
	return EBTNodeResult::Succeeded;
}
