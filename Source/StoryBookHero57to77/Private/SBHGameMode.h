// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UDialogueWidget;

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SBHGameMode.generated.h"




UENUM(BlueprintType)
enum GameStates
{
	Overworld UMETA(DisplayName = "Overworld"),
	Dialogue UMETA(DisplayName = "Dialogue"),
	Combat UMETA(DisplayName = "Combat"),
	LevelTransition UMETA(DisplayName = "LevelTransition"),
	Pause UMETA(DisplayName = "Pause"),
	GameOver UMETA(DisplayName = "Game Over"),
	Inventory UMETA(DisplayName = "Inventory"),
	Shop UMETA(DisplayName = "Shop")

};

/**
 * 
 */
UCLASS()
class ASBHGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

UFUNCTION(BlueprintCallable, Category = GameBase)
void SwitchGameState(GameStates newState);

UFUNCTION(BlueprintCallable, Category = GameBase)
void DialogueFunction(UStorageClass* GameIn);

};
