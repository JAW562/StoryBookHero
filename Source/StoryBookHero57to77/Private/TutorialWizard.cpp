// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWizard.h"

// Sets default values
ATutorialWizard::ATutorialWizard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCol"));

	SphereCol->SetupAttachment(RootComponent);

	SphereCol->SetGenerateOverlapEvents(true);

	SphereCol->OnComponentBeginOverlap.AddDynamic(this, &ATutorialWizard::OnOverlapBegin);

	SphereCol->OnComponentEndOverlap.AddDynamic(this, &ATutorialWizard::OnOverlapEnd);


	SphereCol->SetSphereRadius(30.0f);

	InterTW = CreateDefaultSubobject<UInteractionComponent>(TEXT("InterTW"));

	AddOwnedComponent(InterTW);

	InterTW->OnInteractionBegin.AddDynamic(this, &ATutorialWizard::OnInteractionBegin);








}

// Called when the game starts or when spawned
void ATutorialWizard::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATutorialWizard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Display, TEXT("OverlapBegin"));

	if (OtherActor->IsA(AScrap::StaticClass()))
	{

		UE_LOG(LogTemp, Display, TEXT("ActorFound"));

		scrapThere = true;

	}

}

void ATutorialWizard::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

		scrapThere = false;


}

void ATutorialWizard::UpdateAnim()
{


	if (scrapThere == true)
	{
		UPaperFlipbook* DesiredAnimation = QuestAnim;
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
	else if (scrapThere == false)
	{
		UPaperFlipbook* DesiredAnimation = IdleAnim;
		GetSprite()->SetFlipbook(DesiredAnimation);
	}

}

void ATutorialWizard::OnInteractionBegin()
{
	UE_LOG(LogTemp, Display, TEXT("Interaction Succesful"));
}

// Called every frame
void ATutorialWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnim();


}

