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

	static ConstructorHelpers::FClassFinder<UDialogueWidget> Dialogue(TEXT("/Game/UisnMenus/Dialogue/Dialogue"));


	if (Dialogue.Succeeded())
	{
		UE_LOG(LogTemp, Display, TEXT("Successful"));

		DialogueWidgetClass = Dialogue.Class;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Unsuccessful"));
	}

	dialogueMenu = false;


	InterTW->OnInteractionBegin.AddDynamic(this, &ATutorialWizard::OnInteractionBegin);









}

// Called when the game starts or when spawned
void ATutorialWizard::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATutorialWizard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AScrap::StaticClass()))
	{
		ScrapRef = (AScrap*) OtherActor;

		scrapThere = true;

	}

}

void ATutorialWizard::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{

	if (scrapThere == true)
	{
		scrapThere = false;

	}


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

	if (dialogueMenu == false)
	{
		
		TWDialogue = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);


		if (TWDialogue)
		{

			APlayerController* PC = GetWorld()->GetFirstPlayerController();


			TWDialogue->SetOwningPlayer(PC);

			TWDialogue->SetVisibility(ESlateVisibility::Visible);

			TWDialogue->OppRef = this;

			TWDialogue->ScrapRef = ScrapRef;

			TWDialogue->OppHead = TWHead1;

			TWDialogue->ActorName = "Tutorial Wizard";

			TWDialogue->SetFocus();

			TWDialogue->HasMouseCapture();

			TWDialogue->AddToViewport();

			


			if (TWDialogue->IsInViewport())
			{

				ScrapRef->DisableInput(PC);


				UE_LOG(LogTemp, Display, TEXT("Dialogue Widget Added to Viewport"));

				TArray<FString> TWLines;

				TArray<FString> ScrapLines;

				TWDialogue->ScrapFirst = false;

				TWLines.Add("Hello there.");

				ScrapLines.Add("Hello to you too.");

				TWDialogue->OppDialogue = TWLines;

				TWDialogue->ScrapDialogue = ScrapLines;

				dialogueMenu = true;

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Dialogue Widget Not Added to Viewport"));
			}


		}

	
	}


}

// Called every frame
void ATutorialWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnim();


}

