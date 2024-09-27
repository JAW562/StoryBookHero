// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UDialogueWidget;
class AScrap;

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"
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

	ASBHGameMode();

UFUNCTION(BlueprintCallable, Category = GameBase)
void SwitchGameState(GameStates newState);

UFUNCTION(BlueprintCallable, Category = GameBase)
void DialogueFunction(UStorageClass* GameIn);

UFUNCTION(BlueprintCallable, Category = GameBase)
void CombatFunction(UStorageClass* GameIn);

UFUNCTION(BlueprintCallable, Category = GameBase)
void OverworldFunction(UStorageClass* GameIn);

UPROPERTY(BlueprintReadWrite, Category = GameBase)
TSubclassOf<UDialogueWidget> DialogueWidgetClass;

UPROPERTY(BlueprintReadWrite, Category = GameBase)
TSubclassOf<AScrap> ScrapClass;

};
