// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleUI.h"

void UBattleUI::EndBattleUI()
{

	TArray<UUserWidget*> foundWidgets;

	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundWidgets, UUserWidget::StaticClass(), false);

	for (UUserWidget* Widget : foundWidgets)
	{
		Widget->RemoveFromViewport();

	}



}