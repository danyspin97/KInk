// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SeaStar.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

void ASeaStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FBlackboard::FKey BotStateKey = GetBotController()->GetBlackboardComp()->GetKeyID(TEXT("BotState"));
	EBotState BotState = static_cast<EBotState>(GetBotController()->GetBlackboardComp()->GetValue<UBlackboardKeyType_Enum>(BotStateKey));
	if (BotState == EBotState::BT_Attacking)
	{
		FireTime += DeltaTime;
	}
}

void ASeaStar::Fire(const FVector& Location)
{
	if (!CanFire())
	{
		return;
	}
	Super::Fire();
	for (int32 i = 0; i < NumberOfBullet; ++i)
	{
		const FVector& SeaLocation = GetCapsuleComponent()->GetComponentLocation();
		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(SeaLocation, Location);
		const FVector& Direction = FRotationMatrix(FRotator(Rotation.Pitch, Rotation.Yaw - 10, Rotation.Roll)).GetUnitAxis(EAxis::X);
		PoolRef->PoolProjectile(GetWorld(), Projectile, this->GetClass(), SeaLocation, Rotation, Direction, (float)BulletDamage * GameState->Multiplier);
	}
}

