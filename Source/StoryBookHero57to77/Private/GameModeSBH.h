// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeSBH.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	Overworld   UMETA(DisplayName = "Overworld"),
	Dialogue	UMETA(DisplayName = "Dialogue"),
	Battle		UMETA(DisplayName = "Battle"),
	GameOver	UMETA(DisplayName = "GameOver")

};

/**
 * 
 */
UCLASS()
class AGameModeSBH : public AGameModeBase
{
	GENERATED_BODY()


public:
	
	AGameModeSBH();

	UPROPERTY(BlueprintReadWrite, Category = GameState)
	EGameState CurrentGameState;

	UFUNCTION(BlueprintCallable, Category = GameState)
	void SwitchGameState(EGameState NewState);
	
};
