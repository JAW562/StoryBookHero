// Fill out your copyright notice in the Description page of Project Settings.

//We do this in order to avoid circular dependencies
#include "BattleManager.h"
#include "Scrap.h"
#include "TutorialWizard.h"
#include "StorageClass.h"

// Sets default values
ABattleManager::ABattleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//We want to initiliaze everything here just in case
	ComScrap;

	ComOpp.Empty();

	turnOrder.Empty();

	turnIndex = 0;
	
	//We use constructo helpers to be able to find certain objects and classes without creating subobjects for them
	static ConstructorHelpers::FClassFinder<UBattleUI> Battle(TEXT("/Game/UisnMenus/Battle/MyBattleUI"));

	HandleActionDelegate.AddUniqueDynamic(this, &ABattleManager::HandleAction);
	
	//Check to make sure Battle was found successfully 
	if (Battle.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Successful"));

		BattleUIClass = Battle.Class;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Unsuccessful"));
	}




}




// Called every frame
void ABattleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//BeginPlay is called whenever the level that the object is in is played.
void ABattleManager::BeginPlay()
{
	//Debug purposes
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay started"));

	/*We get the game instance using a Unreal standard function and then cast it and store it into UStorage class, this is okay because we set our game
	* instance to be UStorageClass within our Unreal roject settings.
	*/
	UStorageClass* GameInstance = Cast<UStorageClass>(GetGameInstance());

	//We make sure game instance was found
	if (GameInstance)
	{
		//We check if Scrap.info isn't empty, and if it isn't, we store it into com scrao.
		if(GameInstance->ScrapInfo.actorClass != nullptr)
		{
			ComScrap = GameInstance->ScrapInfo;

		}

		//Add enemies to our enemy array
		if (!(GameInstance->Enemies.IsEmpty()))
		{
			for (FActorInfo i : GameInstance->Enemies)
			{
				ComOpp.Add(i);

			}


		}

		if (!(GameInstance->PrevLevelName.IsNone()))
		{
			PrevLevel = GameInstance->PrevLevelName;
		}

		//After prep has been done, we get to real battle logic
		BattleTime(ComScrap, ComOpp);

	}

}

//Used to set up UI, set up queues, and execute actions.
void ABattleManager::BattleTime(FActorInfo Scrap, TArray<FActorInfo> Opp)
{
	//We create a battle UI
	BattleUI = CreateWidget<UBattleUI>(GetWorld(), BattleUIClass);

	//Make sure our UI exists
	if (BattleUI)
	{
		//Get our player controller so it can be the UIs owner
		APlayerController* PC = GetWorld()->GetFirstPlayerController();


		BattleUI->SetOwningPlayer(PC);

		//Make sure its hidden until player turn
		BattleUI->SetVisibility(ESlateVisibility::Hidden);

		BattleUI->SetFocus();

		BattleUI->HasMouseCapture();

		BattleUI->AddToViewport();

	}

	/*
	* Next couple of lines is kind of redudant but basically we sort our turn order in a vector, then we store the sorted turns in a queue so
	* it is easier to maintain turn order.
	*/

	turnOrder.Add(Scrap);

	for (FActorInfo i : Opp)
	{
		turnOrder.Add(i);
	}

	turnOrder = SortTurn(turnOrder);

	HandleTurn();

}
	



//Sort turn takes in a vector and returns one that has elements sorted by agility to determine who goes first.
TArray<FActorInfo> ABattleManager::SortTurn(TArray<FActorInfo> order)
{
	//We use bubble sort to sort this vector

	//For our loops
	int i, j;
	//Check for our loop to see if we can end it. 
	bool swapped;

	//First loop to iterate through the arrat
	for (i = 0; i < order.Num() - 1; i++)
	{
		//Set our boolean at the beginning so we are able to run through the correct amount of times.
		swapped = false;
		//Second loop to iterate through what is left of the array, this way we don't go out of bounds
		for (j = 0; j < order.Num() - i - 1; j++)
		{
			//We check to see if our current element is less than our next one, if so, we swamp them
			if (order[j].agi < order[j+1].agi)
			{
				FActorInfo temp = order[j];
				order[j] = order[j+1];
				order[j+1] = temp;
				swapped = true;



			}
		}

		//If no elements were swapped by the inner loop, then we break fully.
		if (swapped == false)
			break;

	}

	return order;
}

//Delegates player or AI's turn.
void ABattleManager::HandleTurn()
{

	if (turnIndex <= turnOrder.Num())
	{

		curChar = turnOrder[turnIndex];

		turnOrder.RemoveAt(turnIndex);

		
		if (ComOpp[0].health <= 0 || ComScrap.health <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("BATTLE ENDED"));

			BattleUI->EndBattleUI();

			UGameplayStatics::OpenLevel(this, PrevLevel);
		}


	}

	//Determines whether current character is AI or Player.
	if (curChar.actorClass == AScrap::StaticClass())
	{

		if (ComScrap.health > 0)
		{
			turnOrder.Add(curChar);
		}

		isWaiting = true;

		//Make sure we make UI visible for player turn
		BattleUI->SetVisibility(ESlateVisibility::Visible);
		

		
	}
	//AI turn
	else if (curChar.actorClass == ATutorialWizard::StaticClass())
	{

		if (ComOpp[0].health > 0)
		{
			turnOrder.Add(curChar);
		}
		isWaiting = true; 

		BattleUI->SetVisibility(ESlateVisibility::Hidden);

		HandleAIAction(curChar);

	}



}

//Way our actions will be handled, whether they be attack, defend, skills, or items.
void ABattleManager::HandleAction(FActorInfo character, FString action)
{

	UE_LOG(LogTemp, Warning, TEXT("Action is being handled"));

	ActorInstance = GetWorld()->SpawnActor<AActor>(character.actorClass);

	ActorInstance->SetActorHiddenInGame(true);

	AScrap* ScrapInstance = Cast<AScrap>(ActorInstance);
	
	FActorInfo& opponent = ComOpp[0];

	ScrapInstance->ScrapAttack(opponent, AIDefend, Defend, isWaiting, action);

	UE_LOG(LogTemp, Warning, TEXT("%s"), isWaiting ? TEXT("true") : TEXT("false"));

	ScrapInstance->Destroy();

	HandleTurn();

}

//AI turn, will most likely call a different class for this, class that will handle AI actions in combat
void ABattleManager::HandleAIAction(FActorInfo character)
{
	ActorInstance = GetWorld()->SpawnActor<AActor>(character.actorClass);

	ActorInstance->SetActorHiddenInGame(true);

	ATutorialWizard* EnemyInstance = Cast<ATutorialWizard>(ActorInstance);

	FActorInfo& scrapactual = ComScrap;

	FActorInfo& opponent = character;

	EnemyInstance->AttackCall(scrapactual, opponent, AIDefend, Defend, isWaiting);

	UE_LOG(LogTemp, Warning, TEXT("%s"), isWaiting ? TEXT("true AI") : TEXT("false AI"));

	EnemyInstance->Destroy();

	HandleTurn();

	
}