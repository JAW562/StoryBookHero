// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"


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