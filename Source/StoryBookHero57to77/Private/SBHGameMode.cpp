// Fill out your copyright notice in the Description page of Project Settings.


#include "SBHGameMode.h"
#include "DialogueWidget.h"


void ASBHGameMode::SwitchGameState(GameStates newState)
{
	UStorageClass* GameInstance = Cast<UStorageClass>(GetWorld()->GetGameInstance());

	switch (newState)
	{
	case GameStates::Overworld:
		/*
		* Pseudocode for logic:
		* This will be specfically used to resume the overworld after combat or any kind of level transition.
		* We find where scrap was in the overworld and we spawn them back there, that's it, most other level actors will have static positions
		* From there, it should be fine, everything we need to find will be stored in the game instance.
		*/



		break;

	case GameStates::Dialogue:
		/*
		* Psuedocode for logic:
		* So whenever we want to switch to dialouge, we'll want to spawn the UI controlled by scrap and store all of the planned dialouge.
		* I will most likely have a function to store dialogue or maybe select it based on who their talking to?
		* I have to write all of the dialogue out in the code somwhere anyway so it's not like I'm saving space or anything by including in characters classes.
		* Either way, this state will probably execute functions from dialogue widget, most likely create ones called spawn and select dialogue, something like that.
		* This is the state I'm most iffy on calling.
		*/

		DialogueFunction(GameInstance);



		break;

	case GameStates::Combat:
		/*
		* Pseudocode for logic:
		* We want to figure out what level we're in so we know where to teleport our camera to, AKA, the battlescene of the level. There'll be a camera item in the game instance that will
		* store the battle scene camera. So we disable scrap movement, fetch the camera and focus it. At that time, we spawn in scraps sprite as well as the enemys.
		* That's about it for the state itself.
		*/
		break;

	case GameStates::LevelTransition:
		/*
		* Pseudocode for logic:
		* This is for in level transitions. So stuff like houses and shops.
		* So we figure out where we're trying to go, most likely fetched from the object itself that scrap interacts wtih and then used to spawn scrap in wherever he needs to go.
		* It's all in the same level though so it most likely is just teleportation rather than spawning. 
		*/
		break;

	case GameStates::Pause:
		/*
		* Psuedocode for logic:
		* Handles the pasuse, this will basically just stop movement in the main world and display the pause screen for the player.
		*/
		break;

	case GameStates::GameOver:
		/*
		* Psuedocode for logic:
		* Displays the game over screen and reverts to a moment before combat or allows a player to relaod a save or something.
		*/
		break;

	case GameStates::Inventory:
		/*
		* Psuedocode for logic:
		* After player presses a certain button, inventory will displayed and pause the game around them, may have other screens as well like a map or someting. 
		*/
		break;

	case GameStates::Shop:
		/*
		* Psuedocode for logic:
		* Activated when player interacts with a shopkeeper as their able to access the shopkeeper inventory and buy stuff.
		*/

		break;

	default:

		break;
	}
}

void ASBHGameMode::DialogueFunction(UStorageClass* GameIn)
{
	UDialogueWidget* DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), UDialogueWidget::StaticClass());

	if (DialogueWidget)
	{

		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		DialogueWidget->SpawnWidget(GameIn->NPCDifo, PC);

		if (DialogueWidget->IsInViewport())
		{
			DisableInput(PC);

			UE_LOG(LogTemp, Warning, TEXT("Dialogue Widget Added to Viewport"));

			DialogueWidget->OppDialogue.Add("Hello There.");

			DialogueWidget->ScrapDialogue.Add("Hello to you too.");


		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Dialogue Widget Not Added to Viewport"));
		}

	}
}




