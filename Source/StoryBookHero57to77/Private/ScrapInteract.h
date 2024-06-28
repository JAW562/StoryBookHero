// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperCharacter.h"
#include "InteractionComponent.h"
#include "ScrapInteract.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UScrapInteract : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UScrapInteract();


	//UPROPERTY(BlueprintCallable, Category = "Interactions")
	void InteractionWithScrap(APaperCharacter* ScrapRef);


		
};
