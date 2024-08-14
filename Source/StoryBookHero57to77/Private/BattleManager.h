// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Scrap.h"
#include "BattleManager.generated.h"

UCLASS()
class ABattleManager : public AActor
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Sets default values for this actor's properties
	ABattleManager();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void BeginBattle(AScrap* ScrapRef, ATutorialWizard* OppRef);

	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
