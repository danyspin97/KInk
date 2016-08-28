// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SplineActor.generated.h"

UENUM(BlueprintType)
enum class ESplinePawnType : uint8
{
	RandomType		UMETA(DisplayName = "RandomType"),

	Linear			UMETA(DisplayName = "Linear"),

	ZigZagCurve		UMETA(DisplayName = "ZigZagCurve"),

	ZigZagLinear	UMETA(DisplayName = "ZigZagLinear"),

	// Add more

};

UENUM(BlueprintType)
enum class ESplineProjectileType : uint8
{
	NoSpline        UMETA(DisplayName = "NoSpline"),

	RandomType		UMETA(DisplayName = "RandomType"),

	Linear			UMETA(DisplayName = "Linear"),

	ZigZagCurve		UMETA(DisplayName = "ZigZagCurve"),

	ZigZagLinear	UMETA(DisplayName = "ZigZagLinear"),

	// Add more

};

UCLASS()
class KINK_API ASplineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineActor(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	class USplineComponent* SplineComp;

	class AEnemy* EnemyOwner;

	class AProjectile* ProjectileOwner;

	void InitializeSplinePawn(ESplinePawnType SplineType);

	void InitializeSplineProjectile(ESplineProjectileType SplineType);

	void SetSplinePointsForLinear();

	void SetSplinePointsForZigZagCurve();

	void SetSplinePointsForZigZagLinear();

};