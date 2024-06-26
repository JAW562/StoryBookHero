// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapInteract.h"

// Sets default values for this component's properties
UScrapInteract::UScrapInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*
* The main function of our tool, this will find the nearest actor to scrap that can be interacted with and return the data in form of a
* FHitResultStruct containing the data of that actor
*/

FHitResult UScrapInteract::InteractionWithScrap(APaperCharacter* ScrapRef)
{
	//We get scraps root component so we can get an accurate distance to the nearest actor
	USceneComponent* RC = ScrapRef->GetRootComponent();

	//Get the location of Scrap
	FVector Start = RC->GetComponentLocation();

	//Get the farthest distance we want scrap to be able to interact in
	FVector End = Start + RC->GetComponentRotation().Vector() * 200.0f;

	//Our hit result struct that contains the data of the actor that scraps interact hits
	FHitResult OnHit;

	//Paramters we want the line trace to follow
	FCollisionQueryParams Params; 

	//We add an ignored actor to our parameters, this one being scrap itself
	Params.AddIgnoredActor(ScrapRef);

	//Here we run a single line trace using the varaibles we described above along with a collision channel, this being world static.
	if (GetWorld()->LineTraceSingleByChannel(OnHit, Start, End, ECollisionChannel::ECC_WorldStatic, Params))
	{
		//Returns the information about the actor that gets hit by the line trace
		return OnHit;
	}

	//Return a blank FHitResult for consistency sake
	return FHitResult();

}


// Called when the game starts
void UScrapInteract::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UScrapInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

