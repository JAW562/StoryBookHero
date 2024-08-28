// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATutorialWizard;
class AScrap;

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"PaperFlipbook.h"
#include "StorageClass.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Category = Stroage)
struct FActorInfo {

	GENERATED_USTRUCT_BODY()

	UPaperFlipbook* Sprite;
	UClass* actorClass;


};

UCLASS()
class UStorageClass : public UGameInstance
{
	GENERATED_BODY()

public:
	UStorageClass();

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FActorInfo ScrapInfo;

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	TArray<FActorInfo> Enemies;

	UFUNCTION(BlueprintCallable, Category = Storage)
	void StoreInfo(FActorInfo Info);


};
