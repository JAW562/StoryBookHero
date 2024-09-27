// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATutorialWizard;
class AScrap;

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"PaperFlipbook.h"
#include "PaperCharacter.h"
#include "SBHGameMode.h"
#include "StorageClass.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType, Category = Storage)
struct FActorInfo {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	UPaperFlipbook* Sprite;
	UClass* actorClass;
	int agi;
	int health;
	int ID;


};


USTRUCT(BlueprintType, Category = Storage)
struct FDialogueInfo {

	GENERATED_USTRUCT_BODY()


	AScrap* ScrapRef;
	UTexture2D* OppHead;
	APaperCharacter* Opposition;
	FString ActorName;
	bool ScrapFirst;
	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool CombatAfter;

};

USTRUCT(BlueprintType, Category = Storage)
struct FCombatInfo {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FVector EnemyTransform;
	UPROPERTY(BlueprintReadWrite, Category = Combat)
	AActor* BattleCamera;
	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FRotator EnemyRotation;

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

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FName PrevLevelName;

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FVector ScrapLocation; 

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FRotator ScrapRotation;

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FDialogueInfo NPCDifo;

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FCombatInfo ComInfo;

	UFUNCTION(BlueprintCallable, Category = Storage)
	void StoreInfo(FActorInfo Info);

	UFUNCTION(BlueprintCallable, Category = Storage)
	void StoreLevelName(FName level);




};
