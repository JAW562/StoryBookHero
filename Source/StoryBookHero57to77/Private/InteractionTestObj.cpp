// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTestObj.h"

// Sets default values
AInteractionTestObj::AInteractionTestObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Sets up our interaction component to our object
	InterComp = CreateDefaultSubobject<UITOInter>(TEXT("InteractionComp"));
	
	AddOwnedComponent(InterComp);

	//Creates a static mesh default subobject
	TestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TestMesh"));

	//Sets up our static mesh to be attached to our root component
	TestMesh->SetupAttachment(RootComponent);

	//Here we use the constructor helpers class and the fobjectfinder function to find the object we want to use as our static mesh, in this case, a sphere and store it in a new variable
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TestMeshAsset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	//We check to make sure that our object was able to be found
	if (TestMeshAsset.Object)
	{
		//Here we set our test mesh to be our object we found.
		TestMesh->SetStaticMesh(TestMeshAsset.Object);


	}





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

