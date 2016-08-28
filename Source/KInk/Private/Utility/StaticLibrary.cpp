// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Enemy.h"
#include "Hangar/Projectile.h"
#include "Hangar/PowerUp.h"
#include "StaticLibrary.h"

UStaticLibrary::UStaticLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

bool UStaticLibrary::IsInFrustum(AActor* Actor, UWorld* WorldContext)
{
	ULocalPlayer* LocalPlayer = WorldContext->GetFirstLocalPlayerFromController();
	if (LocalPlayer != nullptr && LocalPlayer->ViewportClient != nullptr && LocalPlayer->ViewportClient->Viewport)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			WorldContext->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, LocalPlayer->ViewportClient->Viewport);
		if (SceneView != nullptr)
		{
			return SceneView->ViewFrustum.IntersectSphere(
				Actor->GetActorLocation(), Actor->GetSimpleCollisionRadius());
		}
	}

	return false;
}

bool UStaticLibrary::IsInFrustum(AProjectile* Projectile, UWorld* WorldContext)
{
	ULocalPlayer* LocalPlayer = WorldContext->GetFirstLocalPlayerFromController();
	if (LocalPlayer != nullptr && LocalPlayer->ViewportClient != nullptr && LocalPlayer->ViewportClient->Viewport)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			WorldContext->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, LocalPlayer->ViewportClient->Viewport);
		if (SceneView != nullptr)
		{
			return SceneView->ViewFrustum.IntersectBox(Projectile->BoxComp->GetComponentLocation(), Projectile->BoxComp->GetScaledBoxExtent());
		}
	}

	return false;
}

bool UStaticLibrary::IsInFrustum(AEnemy* Enemy, UWorld* WorldContext)
{
	ULocalPlayer* LocalPlayer = WorldContext->GetFirstLocalPlayerFromController();
	if (LocalPlayer != nullptr && LocalPlayer->ViewportClient != nullptr && LocalPlayer->ViewportClient->Viewport)
	{
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			WorldContext->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, LocalPlayer->ViewportClient->Viewport);
		if (SceneView != nullptr)
		{
			return SceneView->ViewFrustum.IntersectSphere(
				Enemy->GetCapsuleComponent()->GetComponentLocation(), Enemy->GetCapsuleComponent()->GetScaledCapsuleRadius());
		}
	}

	return false;
}
