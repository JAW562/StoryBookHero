// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "Scrap.h"
#include "StorageClass.h"

// Sets default values
ABattleManager::ABattleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComScrap;

	ComOpp.Empty();

}


void ABattleManager::BeginBattle()
{

}

// Called every frame
void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleManager::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay started"));

	UStorageClass* GameInstance = Cast<UStorageClass>(GetGameInstance());

	if (GameInstance)
	{
		if(GameInstance->ScrapInfo.actorClass != nullptr)
		{
			ComScrap = GameInstance->ScrapInfo;

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(ComScrap.actorClass->GetName()));


		}

		if (!(GameInstance->Enemies.IsEmpty()))
		{
			for (FActorInfo i : GameInstance->Enemies)
			{
				ComOpp.Add(i);

			}

			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(ComOpp[0].actorClass->GetName()));


		}

	}

}

