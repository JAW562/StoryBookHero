// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "BattleUI.generated.h"

/**
 * 
 */
UCLASS()
class UBattleUI : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = Combat)
	void EndBattleUI();

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool TurnEnd;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FString ActionTaken;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	int indexEnemy;

	
	
};
