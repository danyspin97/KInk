// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseBotController.generated.h"

/**
 * 
 */
UCLASS()
class KINK_API ABaseBotController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseBotController(const class FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;

	//UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	//UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;

	AEnemy* EnemyPawn;

	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;

	virtual void BeginInactiveState() override;

	void StopBehaviorTree();

	void StartBehaviorTree();

	FORCEINLINE FVector GetSelfLocation();

	FORCEINLINE FVector GetForwardVector();

	FORCEINLINE class UFloatingPawnMovement* GetCharacterMovement();

	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

};

UENUM(BlueprintType)
enum class EBotState : uint8
{
	BT_Following = 0       UMETA(DisplayName = "Following"),

	// Then the ship execute its main task
	BT_Attacking = 1       UMETA(DisplayName = "Attacking"),
};