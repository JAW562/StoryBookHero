// Fill out your copyright notice in the Description page of Project Settings.


#include "ITOInter.h"

UITOInter::UITOInter()
{

}

void UITOInter::OnInteractionBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted"));
}

void UITOInter::OnInteractionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Stop Interact"));
}