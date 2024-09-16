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
		UE_LOG(LogTemp, Warning, TEXT("Successful"));

		DialogueWidgetClass = Dialogue.Class;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Unsuccessful"));
	}

	dialogueMenu = false;


	InterTW->OnInteractionBegin.AddDynamic(this, &ATutorialWizard::OnInteractionBegin);

	TWAgility = 0;

	combatThere = true;

	ConstructorHelpers::FObjectFinder<UPaperFlipbook>Anim(TEXT("/Game/Levels/TLevel/Flipbooks/Idle"));

	NPCfo.Sprite = Anim.Object;
	NPCfo.actorClass = this->StaticClass();
	NPCfo.agi = 0;
	NPCfo.health = 50;
	NPCfo.ID = 1;







}

// Called when the game starts or when spawned
void ATutorialWizard::BeginPlay()
{

	Super::BeginPlay();

	GameMode = Cast<ASBHGameMode>(GetWorld()->GetAuthGameMode());

	GameIn = Cast<UStorageClass>(GetWorld()->GetGameInstance());

	
}

void ATutorialWizard::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(AScrap::StaticClass()))
	{
		ScrapRef = (AScrap*) OtherActor;

		scrapThere = true;

	}
	else
	{


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

	if (dialogueMenu == false && ScrapRef != NULL)
	{

		GameIn->NPCDifo.ActorName = "Tutorial Wizard";
		GameIn->NPCDifo.OppHead = TWHead1;
		GameIn->NPCDifo.ScrapFirst = false;
		GameIn->NPCDifo.ScrapRef = ScrapRef;
		GameIn->NPCDifo.Opposition = this;
		GameIn->NPCDifo.CombatAfter = true;

		GameMode->SwitchGameState(GameStates::Dialogue);

		dialogueMenu = true;


	
	}


}

void ATutorialWizard::CallBattle()
{
	if (combatThere == true)
	{

		if (GameIn)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameInstance Found"));

			if (ScrapRef)
			{ 

				GameIn->StoreInfo(ScrapRef->ScrapInformation);

			}

			if (this)
			{

				GameIn->StoreInfo(NPCfo);


			}

			UE_LOG(LogTemp, Warning, TEXT("%s"), GetLevel()->GetFName());







		}

		if (!(GameIn->Enemies.IsEmpty()) && GameIn->ScrapInfo.actorClass != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Level opened"));
			UGameplayStatics::OpenLevel(this, "/Game/Levels/BattleScenes/BattleSceneForest");
		}

	}

}

// Called every frame
void ATutorialWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnim();


}

void ATutorialWizard::AttackCall(FActorInfo& ScrapInfo, FActorInfo& itself,  bool& AFlag, bool& SFlag, bool& Wait)
{

	if (AFlag == true)
	{
		AFlag = false;
	}

	if (ScrapInfo.health > 0 && itself.health > 25)
	{
		if (SFlag == true)
		{
			ScrapInfo.health -= 5;

			UE_LOG(LogTemp, Warning, TEXT("AI Attack"));
		}
		else 
		{
			ScrapInfo.health -= 10;

			UE_LOG(LogTemp, Warning, TEXT("AI Attack"));
		}


	}
	else if (itself.health < 25)
	{
		AFlag = true;
		UE_LOG(LogTemp, Warning, TEXT("AI Defend"));

	}

	Wait = false;
}

