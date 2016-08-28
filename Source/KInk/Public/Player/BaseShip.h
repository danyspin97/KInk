// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "BaseShip.generated.h"

UCLASS(config = Game)
class KINK_API ABaseShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseShip(const class FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	/*UFUNCTION()
	void OnBeginOverlap(AActor* OtherActor);*/

	virtual void StopMovement();

	FORCEINLINE class UPaperFlipbookComponent* GetSprite() { return Sprite; };

	FORCEINLINE class UFloatingPawnMovement* GetCharacterMovement() { return PawnMovement; };

	FORCEINLINE class UCapsuleComponent* GetCapsuleComponent() { return CapsuleComponent; };

protected:
	//UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//class ;

	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(Category = "Character", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* Sprite;

	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* PawnMovement;
};
