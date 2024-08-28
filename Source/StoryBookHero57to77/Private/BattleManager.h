// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AScrap;
class UStorageClass;

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperCharacter.h"
#include "StorageClass.h"
#include "BattleManager.generated.h"

UCLASS()
class ABattleManager : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void BeginBattle();

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	FActorInfo ComScrap;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	TArray<FActorInfo> ComOpp;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;



};
