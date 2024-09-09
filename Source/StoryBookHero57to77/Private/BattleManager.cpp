// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "Scrap.h"
#include "TutorialWizard.h"
#include "StorageClass.h"

// Sets default values
ABattleManager::ABattleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ComScrap;

	ComOpp.Empty();

	turnOrder.empty();

	currentTurn.empty();

	static ConstructorHelpers::FClassFinder<UBattleUI> Battle(TEXT("/Game/UisnMenus/Battle/MyBattleUI"));
	
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

void ABattleManager::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay started"));

	UStorageClass* GameInstance = Cast<UStorageClass>(GetGameInstance());

	if (GameInstance)
	{
		if(GameInstance->ScrapInfo.actorClass != nullptr)
		{
			ComScrap = GameInstance->ScrapInfo;

		}

		if (!(GameInstance->Enemies.IsEmpty()))
		{
			for (FActorInfo i : GameInstance->Enemies)
			{
				ComOpp.Add(i);

			}


		}


		BattleTime(ComScrap, ComOpp);

	}

}

void ABattleManager::BattleTime(FActorInfo Scrap, TArray<FActorInfo> Opp)
{

	BattleUI = CreateWidget<UBattleUI>(GetWorld(), BattleUIClass);


	if (BattleUI)
	{

		APlayerController* PC = GetWorld()->GetFirstPlayerController();


		BattleUI->SetOwningPlayer(PC);

		BattleUI->SetVisibility(ESlateVisibility::Hidden);

		BattleUI->SetFocus();

		BattleUI->HasMouseCapture();

		BattleUI->AddToViewport();

	}

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



std::vector<FActorInfo> ABattleManager::SortTurn(std::vector<FActorInfo> order)
{
	for (size_t k = 0; k<order.size(); k++)
	{
		if (k+1 <= order.size()-1)
		{
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

void ABattleManager::HandleTurn(FActorInfo character)
{

	if (character.actorClass == AScrap::StaticClass())
	{

		BattleUI->SetVisibility(ESlateVisibility::Visible);

		if (BattleUI->TurnEnd == true)
		{
			HandleAction(character, BattleUI->ActionTaken);
		}
		
	}
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

void ABattleManager::HandleAction(FActorInfo character, FString action)
{

	if (action == "Attack")
	{

	}
	else if (action == "Defend")
	{

	}

}

void ABattleManager::HandleAIAction(FActorInfo character)
{

}