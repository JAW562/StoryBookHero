// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Scrap.h"


void UDialogueWidget::EndConvo(AScrap* Scrap, APlayerController* PC)
{

	TArray<UUserWidget*> foundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundWidgets, UUserWidget::StaticClass(), false);

	for (UUserWidget* Widget : foundWidgets)
	{
		Widget->RemoveFromViewport();

	}


	ScrapRef->EnableInput(PC);


}

void UDialogueWidget::ClearText()
{
	TArray<UUserWidget*> foundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundWidgets, UTextBoxC::StaticClass(), false);

	for (UUserWidget* Text : foundWidgets)
	{
		Text->RemoveFromViewport();
	}


}

void UDialogueWidget::SpawnWidget(FDialogueInfo StoredInfo, APlayerController* PC)
{

	UE_LOG(LogTemp, Warning, TEXT("Got to widget spawn"));

	this->SetOwningPlayer(PC);

	this->SetVisibility(ESlateVisibility::Visible);

	this->OppRef = StoredInfo.Opposition;

	this->ScrapRef = StoredInfo.ScrapRef;

	this->OppHead = StoredInfo.OppHead;

	this->ActorName = StoredInfo.ActorName;

	ScrapFirst = StoredInfo.ScrapFirst;

	this->SetFocus();

	this->HasMouseCapture();

	this->AddToViewport();
}