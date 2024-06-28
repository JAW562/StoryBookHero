// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "ITOInter.h"
#include "InteractionTestObj.generated.h"

UCLASS()
class AInteractionTestObj : public AActor
{
	GENERATED_BODY()

	//In case we need a static mesh, for now, we do not
	//UPROPERTY(VsibleAnywhere, BlueprintReadWrite, Category = Interactions, meta = (AllowPrivateAcess = "true"))
	//class UStaticMeshComponent* InteractMesh;

	
public:	

	// Sets default values for this actor's properties
	AInteractionTestObj();

	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = Interactions)
	class UITOInter* InterComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Interactions)
	class UStaticMeshComponent* TestMesh;


};
 