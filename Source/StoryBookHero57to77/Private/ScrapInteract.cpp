// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrapInteract.h"

// Sets default values for this component's properties
UScrapInteract::UScrapInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

/*
* The main function of our tool, this will find the nearest actor to scrap that can be interacted with and return the data in form of a
* FHitResultStruct containing the data of that actor
*/

void UScrapInteract::InteractionWithScrap(APaperCharacter* ScrapRef)
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
		/*
		* Incredibly important. This does a check to see if the actor that we hit has an interaction component to it, and, if it does, it executes that interaction.
		* We do this by checking if the actor has an interaction component and then casting it to an interaction component to do the subsqeuent logic.
		*/
		if (UInteractionComponent* IComp = Cast<UInteractionComponent>(OnHit.GetActor()->GetComponentByClass(UInteractionComponent::StaticClass())))
		{
			//We call the begin interaction function from our interaction component which fetches the logic from our desired interaction. 
			IComp->BeginInteraction();
		}
	}

}


