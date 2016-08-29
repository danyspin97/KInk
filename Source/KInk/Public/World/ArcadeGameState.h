// Copyright (c) 2016 WiseDragonStd

#pragma once

#include "GameFramework/GameState.h"
#include "ArcadeGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	// When bot isn't runing any behavior tree
	GS_InMainMenu      UMETA(DisplayName = "In Main Menu"),

	// Then the ship has moved near the screen and it is entering it
	GS_InOptionsMenu   UMETA(DisplayName = "In Options Menu"),

	// The ship is waiting before doing an action or attacking
	GS_InGame          UMETA(DisplayName = "In Game"),

	// Then the ship execute its main task
	GS_InPause        UMETA(DisplayName = "In Pause"),

	GS_InGameOver     UMETA(DisplayName = "In Game Over"),
};

USTRUCT(BlueprintType)
struct FScoreBoard
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	FString Nickname;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	int32 Score;

	FORCEINLINE bool MinorTo(const FScoreBoard& Other)
	{
		return Score < Other.Score;
	}

	FScoreBoard()
		: Nickname(TEXT("K-Ink")),
		  Score(FMath::Rand() * 1000)
	{
	}

	FScoreBoard(FString NickName, int32 Score)
	{
		this->Nickname = NickName;
		this->Score = Score;
	}

};


/**
 * 
 */
UCLASS()
class KINK_API AArcadeGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
	EGameState InGameState;

	int32 Wave;

	int32 DifficultyCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
	FString EnemyWaveString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
	FString DifficultString;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
	float StringOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameState)
	bool bIsTextFading;

	float Multiplier;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
	TArray<FScoreBoard> ScoreList;

};
