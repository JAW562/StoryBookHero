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

	turnOrder.empty();

	currentTurn.empty();
	
	//We use constructo helpers to be able to find certain objects and classes without creating subobjects for them
	static ConstructorHelpers::FClassFinder<UBattleUI> Battle(TEXT("/Game/UisnMenus/Battle/MyBattleUI"));
	
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
	size_t TurnIndex = 0;

	turnOrder.push_back(Scrap);

	for (FActorInfo i : Opp)
	{
		turnOrder.push_back(i);
	}

	turnOrder = SortTurn(turnOrder);


	for (FActorInfo k : turnOrder)
	{
		currentTurn.push(k);

	}

	for (size_t l = 0; l <= currentTurn.size(); l++)
	{
		curChar = currentTurn.front();

		currentTurn.pop();

		HandleTurn(curChar);


	}
	



}


//Sort turn takes in a vector and returns one that has elements sorted by agility to determine who goes first.
std::vector<FActorInfo> ABattleManager::SortTurn(std::vector<FActorInfo> order)
{
	for (size_t k = 0; k<order.size(); k++)
	{
		//Since size is zero terminated, we have to do size -1.
		if (k+1 <= order.size()-1)
		{
			//Sorting logic, compares current element with next element and switches if aglitiy is better. NEED ANOTHER LOOP TO FULLY WORK?
			if (order.at(k).agi < order.at(k+1).agi)
			{
				UE_LOG(LogTemp, Warning, TEXT("Succeeded"));

				FActorInfo temp = order.at(k);

				order.at(k) = order.at(k + 1);

				order.at(k + 1) = temp;

			}


		}
	}

	return order;
}

//Delegates player or AI's turn.
void ABattleManager::HandleTurn(FActorInfo character)
{
	//Determines whether current character is AI or Player.
	if (character.actorClass == AScrap::StaticClass())
	{
		//Make sure we make UI visible for player turn
		BattleUI->SetVisibility(ESlateVisibility::Visible);

		//THIS WILL NOT WORK< NEED TO USE TIMERS OR BROADCAST EVENTS
		if (BattleUI->TurnEnd == true)
		{
			HandleAction(character, BattleUI->ActionTaken);
		}
		
	}
	//AI turn
	else if (character.actorClass == ATutorialWizard::StaticClass())
	{
		BattleUI->SetVisibility(ESlateVisibility::Hidden);


		UE_LOG(LogTemp, Warning, TEXT("NPC Turn"));

		if (BattleUI->TurnEnd == true)
		{
			HandleAIAction(character);
		}

	}

}

//Way our actions will be handled, whether they be attack, defend, skills, or items.
void ABattleManager::HandleAction(FActorInfo character, FString action)
{

	if (action == "Attack")
	{

	}
	else if (action == "Defend")
	{

	}

}

//AI turn, will most likely call a different class for this, class that will handle AI actions in combat
void ABattleManager::HandleAIAction(FActorInfo character)
{

}