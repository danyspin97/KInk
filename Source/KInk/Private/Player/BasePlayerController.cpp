// Fill out your copyright notice in the Description page of Project Settings.

#include "KInk.h"
#include "Kraken.h"
#include "HUD/CustomHUD.h"
#include "World/ArcadeGameState.h"
#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{

}

void ABasePlayerController::BeginPlay()
{
	/*FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewport(true);
	InputMode.SetHideCursorDuringCapture(false);*/
	//this->SetInputMode(InputMode);
	bShowMouseCursor = true;
	FTimerHandle FPSTimerHandle;
	GetWorldTimerManager().SetTimer(FPSTimerHandle, this, &ABasePlayerController::ShowFrameRate, 1.f, true);
	SetControlRotation(FRotator(-90, 0, 0));
	//ConsoleCommand(TEXT("r.setRes 1024x760w"), true);
	ConsoleCommand(TEXT("t.maxfps 60"), true);
	ConsoleCommand(TEXT("r.ScreenPertentage 100"), true);
	ConsoleCommand(TEXT("r.ViewDistanceScale 0.6"), true);
	ConsoleCommand(TEXT("r.PostProcessAAQuality 6"), true);
	ConsoleCommand(TEXT("sg.PostProcessQuality 3"), true);
	ConsoleCommand(TEXT("r.Upscale.Quality 3"), true);
	ConsoleCommand(TEXT("sg.ShadowQuality 3"), true);
	ConsoleCommand(TEXT("sg.TextureQuality 3"), true);
	ConsoleCommand(TEXT("sg.EffectsQuality 3"), true);
	//ConsoleCommand(TEXT("show stats"), true);
	this->SetTickableWhenPaused(false);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	FInputActionBinding& Esc = InputComponent->BindAction("Esc", IE_Pressed, this, &ABasePlayerController::EscPressed);
	Esc.bExecuteWhenPaused = true;
	InputComponent->BindAxis("MoveUp", this, &ABasePlayerController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ABasePlayerController::MoveRight);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ABasePlayerController::ShootPressed);
	InputComponent->BindAction("Shoot", IE_Released, this, &ABasePlayerController::ShootReleased);
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FPS++;
	auto CustomPlayerState = Cast<ACustomPlayerState>(PlayerState);
	// Replace with CanFire()
	if (!CustomPlayerState->bBigKraken)
	{
		FHitResult HitResult;
		FVector MouseLocation, MouseWorld;
		DeprojectMousePositionToWorld(MouseLocation, MouseWorld);
		auto pawn = Cast<AKraken>(this->GetPawn());
		const FRotator& Rotation = UKismetMathLibrary::FindLookAtRotation(pawn->GetCapsuleComponent()->GetComponentLocation(), MouseLocation);
		const FRotator& RotationAdj = FRotator(0, Rotation.Yaw + 270, 0);
		pawn->GetCapsuleComponent()->SetWorldRotation(RotationAdj);
		pawn->FireRotation = RotationAdj;
		if (bIsFiring)
		{
			pawn->Fire(DeltaSeconds);
		}
	}
}

void ABasePlayerController::EscPressed()
{
	auto GameState = Cast<AArcadeGameState>(GetWorld()->GetGameState());
	auto CustomHUD = Cast<ACustomHUD>(GetHUD());
	switch (GameState->InGameState)
	{
	case EGameState::GS_InMainMenu:
		GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("Quit"));
		break;
	case EGameState::GS_InGame:
		CustomHUD->SetVisiblePauseWidget();
		GameState->InGameState = EGameState::GS_InPause;
		break;
	case EGameState::GS_InPause:
		CustomHUD->SetInvisiblePauseWidget();
		GameState->InGameState = EGameState::GS_InGame;
		break;
	case EGameState::GS_InGameOver:
		CustomHUD->SetVisibleMainMenu();
		GameState->InGameState = EGameState::GS_InMainMenu;
		break;
	default:
		break;
	}
}

FVector ABasePlayerController::GetCameraLocation()
{
	auto pawn = Cast<AKraken>(this->GetPawn());
	if (pawn)
	{
		return pawn->CameraComponent->GetComponentLocation();
	}
	return FVector::FVector();
}

FVector ABasePlayerController::GetPlayerLocation()
{
	auto pawn = Cast<AKraken>(this->GetPawn());
	if (pawn)
	{
		return pawn->GetCapsuleComponent()->GetComponentLocation();
	}
	return FVector::FVector();
}

void ABasePlayerController::MoveUp(float Value)
{
	auto GameState = Cast<AArcadeGameState>(GetWorld()->GetGameState());
	if (GameState && GameState->InGameState == EGameState::GS_InGame)
	{
		auto pawn = Cast<AKraken>(this->GetPawn());
		if (pawn)
		{
			pawn->MoveUp(Value);
		}
	}
}

void ABasePlayerController::MoveRight(float Value)
{
	auto GameState = Cast<AArcadeGameState>(GetWorld()->GetGameState());
	if (GameState && GameState->InGameState == EGameState::GS_InGame)
	{
		auto pawn = Cast<AKraken>(this->GetPawn());
		if (pawn)
		{
			pawn->MoveRight(Value);
		}
	}
}

void ABasePlayerController::ShootPressed()
{
	bIsFiring = true;
}

void ABasePlayerController::ShootReleased()
{
	bIsFiring = false;
}

bool ABasePlayerController::SnapToViewFrustum(const FVector& worldPosition, FVector* outSnapped)
{
	// Gently borrowed from APlayerController::ProjectWorldLocationToScreen to initialize the SceneView.
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer != NULL && LocalPlayer->ViewportClient != NULL && LocalPlayer->ViewportClient->Viewport != NULL)
	{
		// Create a view family for the game viewport
		FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
			LocalPlayer->ViewportClient->Viewport,
			GetWorld()->Scene,
			LocalPlayer->ViewportClient->EngineShowFlags)
			.SetRealtimeUpdate(true));

		// Calculate a view where the player is to update the streaming from the players start location
		FVector ViewLocation;
		FRotator ViewRotation;
		FSceneView* SceneView = LocalPlayer->CalcSceneView(&ViewFamily, /*out*/ ViewLocation, /*out*/ ViewRotation, LocalPlayer->ViewportClient->Viewport);

		if (SceneView)
		{
			// Transform our world position into projection coordinates.
			auto ProjPosAug = SceneView->ViewProjectionMatrix.TransformPosition(worldPosition);
			FVector ProjPos(ProjPosAug);
			// Divide by the augmented coord W value.
			ProjPos /= ProjPosAug.W;
			// Clamp position to -1,1 on x and y (corresponds to on-screen)
			ProjPos.X = FMath::Clamp<float>(ProjPos.X, -0.87, 0.87);//-1, 1);
			ProjPos.Y = FMath::Clamp<float>(ProjPos.Y, -0.90, 0.90);//-1, 1);
			// Invert the transform back to world space.
			auto AugWorldSnapped = SceneView->InvViewProjectionMatrix.TransformPosition(ProjPos);
			FVector SnapPos(AugWorldSnapped);
			SnapPos /= AugWorldSnapped.W;
			*outSnapped = SnapPos;
			return true;
		}
	}
	return false;
}

void ABasePlayerController::ShowFrameRate()
{
	FPSCount = FPS;
	FPS = 0;
}

bool ABasePlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate)
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewport(!bPause);
	this->SetInputMode(InputMode);
	return Super::SetPause(bPause, CanUnpauseDelegate);
}

