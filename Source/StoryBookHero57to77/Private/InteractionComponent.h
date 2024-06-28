// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

/*
* This is our what will allow us to make interactions between actors and our main character
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	//Here we add a field for a mesh type so we know what kind of mesh to look for with our line traces. This is useful if we had a door and just wanted the door handle to be interacted with. 
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactions)
	//FComponentReference& MeshType;
	

	//A virtual fucntion we want to use and override with each interaction we set up. Will have the logic for what will happen once it begins.
	virtual void OnInteractionBegin();

	//A virtual fucntion we want to use and override with each interaction we set up. Will have the logic for what will happen once it ends.
	//virtual void OnInteractionEnd();



		
};
