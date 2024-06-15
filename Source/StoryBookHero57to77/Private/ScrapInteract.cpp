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


FHitResult UScrapInteract::Interaction(APaperCharacter* ScrapRef)
{

	USceneComponent* RC = ScrapRef->GetRootComponent();

	FVector Start = RC->GetComponentLocation();

	FVector End = Start + RC->GetComponentRotation().Vector() * 200.0f;

	FHitResult OnHit = nullptr;

	FCollisionQueryParams Params; 

	Params.AddIgnoredActor(ScrapRef);

	if (GetWorld()->LineTraceSingleByChannel(OnHit, Start, End, ECollisionChannel::ECC_WorldStatic, Params))
	{
		return OnHit;
	}


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

