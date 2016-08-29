// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "PaperFlipbookActor.h"
#include "World/MessageInterface.h"
#include "Projectile.generated.h"

enum class ESplineProjectileType : uint8;


UCLASS()
class KINK_API AProjectile : public APaperFlipbookActor, public IMessageInterface
{
	GENERATED_BODY()
public:	
	
	AProjectile(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Pool(UClass* OwnerClass, const FVector& Direction, int16 Damage, bool bIsCharacterOwning);

	void Deactivate();

	UFUNCTION()
	virtual void OnBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnMessage(struct FMessage Message) override;

	int16 Damage;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int16 BaseVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	TSubclassOf<class ASplineActor> BP_Spline;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	ESplineProjectileType SplineType;

	float DistanceAlongSpline;

	class ASplineActor* Spline;

	float CurrentVelocity;

	UPROPERTY(EditDefaultsOnly, Category = Attack)
	int16 Acceleration;

	FVector Direction;

	bool bIsCharacterOwning;

	UClass* OwnerClass;
};
