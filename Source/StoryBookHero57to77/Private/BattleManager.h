// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//We do this to avoid circular dependices
class AScrap;
class UStorageClass;
class ATutorialWizard;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperCharacter.h"
#include "StorageClass.h"
#include "BattleUI.h"
#include "Delegates/Delegate.h"
#include "BattleManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHandleActionSignature, FActorInfo, character, FString, action);




UCLASS()
class ABattleManager : public AActor
{
	GENERATED_BODY()



	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void BattleTime(FActorInfo Scrap, TArray<FActorInfo> Opp);

	UFUNCTION(BlueprintCallable, Category = Combat)
	TArray<FActorInfo> SortTurn(TArray<FActorInfo> order);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleTurn();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleAction(FActorInfo character, FString action);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleAIAction(FActorInfo character);

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FName PrevLevel;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FActorInfo ComScrap;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	AActor* ActorInstance;

	UPROPERTY(BlueprintCallable, Category = Combat)
	FHandleActionSignature HandleActionDelegate;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	TArray<FActorInfo> ComOpp;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FActorInfo curChar;
	
	UPROPERTY(BlueprintReadWrite, Category = Combat)
	class UBattleUI* BattleUI;

	UPROPERTY(BlueprintReadWrite,  Category = Combat)
	TSubclassOf<UBattleUI> BattleUIClass;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	TArray<FActorInfo>turnOrder;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool Defend;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool AIDefend;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool isWaiting;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	int turnIndex;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;



};
