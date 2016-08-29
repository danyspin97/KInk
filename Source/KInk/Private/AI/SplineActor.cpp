// Copyright (c) 2016 WiseDragonStd

#include "KInk.h"
#include "Components/SplineComponent.h"
#include "Enemy.h"
#include "Pooling.h"
#include "Player/BasePlayerController.h"
#include "Hangar/Projectile.h"
#include "SplineActor.h"


// Sets default values
ASplineActor::ASplineActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	SplineComp = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("SplineComp"));
	SplineComp->SetUnselectedSplineSegmentColor(FLinearColor::Black);
	SplineComp->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASplineActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASplineActor::InitializeSplinePawn(ESplinePawnType SplineType)
{
	switch (SplineType)
	{
	case ESplinePawnType::RandomType:
		//ESplineType Random = static_cast<ESplineType>(FMath::RandRange(0, 2));
		InitializeSplinePawn(static_cast<ESplinePawnType>(FMath::RandRange(1, 3)));
		break;
	case ESplinePawnType::Linear:
		SetSplinePointsForLinear();
		break;
	case ESplinePawnType::ZigZagCurve:
		SetSplinePointsForZigZagCurve();
		break;
	case ESplinePawnType::ZigZagLinear:
		SetSplinePointsForZigZagLinear();
		break;
	default:
		break;
	}
}

void ASplineActor::InitializeSplineProjectile(ESplineProjectileType SplineType)
{
	switch (SplineType)
	{
	case ESplineProjectileType::NoSpline:
		SplineComp->ClearSplinePoints();
		break;
	case ESplineProjectileType::RandomType:
		//ESplineType Random = static_cast<ESplineType>(FMath::RandRange(0, 2));
		InitializeSplineProjectile(static_cast<ESplineProjectileType>(FMath::RandRange(2, 4)));
		break;
	case ESplineProjectileType::Linear:
		SetSplinePointsForLinear();
		break;
	case ESplineProjectileType::ZigZagCurve:
		SetSplinePointsForZigZagCurve();
		break;
	case ESplineProjectileType::ZigZagLinear:
		SetSplinePointsForZigZagLinear();
		break;
	default:
		break;
	}
}


void ASplineActor::SetSplinePointsForLinear()
{
	SplineComp->ClearSplinePoints();
	TArray<FVector> Points;
	FVector OwnerLocation;
	if (EnemyOwner)
	{
		OwnerLocation = EnemyOwner->GetCapsuleComponent()->GetComponentLocation();
	}
	else if (ProjectileOwner)
	{
		OwnerLocation = ProjectileOwner->BoxComp->GetComponentLocation();
	}
	else
	{
		return;
	}
	Points.Add(FVector::FVector(OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z));
	Points.Add(FVector::FVector(OwnerLocation.X, OwnerLocation.Y - 2000, OwnerLocation.Z));
	SplineComp->SetSplineWorldPoints(Points);
	for (int i = 0; i < SplineComp->GetNumberOfSplinePoints(); i++)
	{
		SplineComp->SetSplinePointType(i, ESplinePointType::Linear);
	}

}

void ASplineActor::SetSplinePointsForZigZagCurve()
{
	SplineComp->ClearSplinePoints();
	TArray<FVector> Points;

	auto ThePC = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!ThePC)
	{
		return;
	}

	FVector OwnerLocation;
	if (EnemyOwner)
	{
		OwnerLocation = EnemyOwner->GetCapsuleComponent()->GetComponentLocation();
	}
	else if (ProjectileOwner)
	{
		OwnerLocation = ProjectileOwner->BoxComp->GetComponentLocation();
	}
	else
	{
		return;
	}

	int32 RightPointX = OwnerLocation.X + 230;
	int32 LeftPointX = OwnerLocation.X - 230;
	int32 VerticalPointY = OwnerLocation.Y;
	const FVector &CameraLocation = ThePC->GetCameraLocation();
	bool LeftRight = false;
	Points.Add(FVector::FVector(VerticalPointY, OwnerLocation.Y, OwnerLocation.Z));
	for (int32 i = 0; CameraLocation.Y < VerticalPointY; i++)
	{
		if (LeftRight)
		{
			Points.Add(FVector::FVector(VerticalPointY, RightPointX, OwnerLocation.Z));
			LeftRight = !LeftRight;
		}
		else
		{
			Points.Add(FVector::FVector(VerticalPointY, LeftPointX, OwnerLocation.Z));
			LeftRight = !LeftRight;
		}
		VerticalPointY -= 300;
	}
	SplineComp->SetSplineWorldPoints(Points);
	for (int i = 0; i < SplineComp->GetNumberOfSplinePoints(); i++)
	{
		SplineComp->SetSplinePointType(i, ESplinePointType::Curve);
	}
}

void ASplineActor::SetSplinePointsForZigZagLinear()
{
	SplineComp->ClearSplinePoints();
	TArray<FVector> Points;

}
