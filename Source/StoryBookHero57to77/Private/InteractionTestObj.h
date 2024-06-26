// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionComponent.h"
#include "Engine/StaticMesh.h"
#include "InteractionTestObj.generated.h"

UCLASS()
class AInteractionTestObj : public AActor
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Interactions, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComp;

	//In case we need a static mesh, for now, we do not
	//UPROPERTY(VsibleAnywhere, BlueprintReadWrite, Category = Interactions, meta = (AllowPrivateAcess = "true"))
	//class UStaticMeshComponent* InteractMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	

	// Sets default values for this actor's properties
	AInteractionTestObj();

	UPROPERTY(BlueprintReadWrite, Category= Interactions)
	UStaticMeshComponent* TestMesh;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
 