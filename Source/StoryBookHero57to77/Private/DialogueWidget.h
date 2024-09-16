// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AScrap;

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperCharacter.h"
#include "TextBoxC.h"
#include "StorageClass.h"
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

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void ClearText();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void SpawnWidget(FDialogueInfo StoredInfo, APlayerController* PC);



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

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	UTexture2D* OppHead;

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	FString ActorName;




	
};
