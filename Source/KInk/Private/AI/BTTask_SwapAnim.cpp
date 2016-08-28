// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Enemy/Jellyfish.h"
#include "PaperFlipbookComponent.h"
#include "BTTask_SwapAnim.h"

EBTNodeResult::Type UBTTask_SwapAnim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseBotController* Controller = Cast<ABaseBotController>(OwnerComp.GetAIOwner());
	if (!Controller)
	{
		return EBTNodeResult::Failed;
	}

	auto pawn = Cast<AJellyfish>(Controller->GetPawn());

	if (!pawn)
	{
		return EBTNodeResult::Failed;
	}

	if (pawn->GetSprite()->GetFlipbook() == pawn->IdleAnim->GetFlipbook())
	{
		pawn->GetSprite()->SetFlipbook(pawn->AlternativeAnim->GetFlipbook());
		
	}
	else
	{
		pawn->GetSprite()->SetFlipbook(pawn->IdleAnim->GetFlipbook());
	}
	return EBTNodeResult::Succeeded;
}


