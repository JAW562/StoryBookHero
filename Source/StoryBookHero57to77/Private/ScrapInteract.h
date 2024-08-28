// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class APaperCharacter; // Forward declaration of PaperCharacter
class UInteractionComponent; // Forward declaration of InteractionComponent

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
