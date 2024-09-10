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
#include "BattleManager.generated.h"


//Enumerations help differentiate states so you can have proper flags and execute certain things in certain states
UENUM(BlueprintType)
enum CombatState
{
	WaitingForPlayerInput UMETA(DisplayName = "Waiting for player input"),
	ResolvingAction UMETA(DisplayName = "Resolving Action"),
	AISelectingAction UMETA(DisplayName = "AISelectingAction")
};


UCLASS()
class ABattleManager : public AActor
{
	GENERATED_BODY()



	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void BattleTime(FActorInfo Scrap, TArray<FActorInfo> Opp);

	std::vector<FActorInfo> SortTurn(std::vector<FActorInfo> order);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleTurn(FActorInfo character);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleAction(FActorInfo character, FString action);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void HandleAIAction(FActorInfo character);

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FActorInfo ComScrap;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	TArray<FActorInfo> ComOpp;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FActorInfo curChar;
	
	UPROPERTY(BlueprintReadWrite, Category = Combat)
	class UBattleUI* BattleUI;

	UPROPERTY(BlueprintReadWrite,  Category = Combat)
	TSubclassOf<UBattleUI> BattleUIClass;

	//Any standard classes cannot have UPROPERTY or UFUNCTION
	std::vector<FActorInfo>turnOrder;

	std::queue<FActorInfo>currentTurn;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;



};
