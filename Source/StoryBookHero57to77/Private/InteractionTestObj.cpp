// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTestObj.h"

// Sets default values
AInteractionTestObj::AInteractionTestObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComp"));

	//No clue if this works, I bascially just want to make it the root component rather than something else.
	//InteractionComp->MeshType = Cast<FComponentReference>(RootComponent);

	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));

	ConstructorHelpers::FObjectFind UStaticMesh* Asset = Sphere



}

void OnInteractionBegin() 
{

	UE_LOG(LogTemp, Warning, TEXT("Interacted"));


}


void OnInteractionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("InteracionEnd"));
}


// Called when the game starts or when spawned
void AInteractionTestObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionTestObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

