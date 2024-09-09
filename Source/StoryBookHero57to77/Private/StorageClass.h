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
	int agi;
	int health;
	int ID;


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

	UFUNCTION(BlueprintCallable, Category = Storage)
	UPaperFlipbook* GetSprite(FActorInfo Info);

	UFUNCTION(BlueprintCallable, Category = Stroage)
	UClass* GetActorClass(FActorInfo Info);

	UFUNCTION(BlueprintCallable, Category = Storage)
	int GetAgility(FActorInfo Info);


};
