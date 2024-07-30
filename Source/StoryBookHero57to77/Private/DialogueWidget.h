// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scrap.h"
#include "PaperCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void EndConvo( AScrap* Scrap, APlayerController* PC);


	//We create two TArrays, meaning dynamically sized and accessible, for Scraps Dialogue and our NPCs
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	TArray<FString> OppDialogue;

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	TArray<FString> ScrapDialogue;

	//Ref for Scrap
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	AScrap* ScrapRef;

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	bool ScrapFirst;

	//Ref for Opposing Character
	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	APaperCharacter* OppRef;


	
};
