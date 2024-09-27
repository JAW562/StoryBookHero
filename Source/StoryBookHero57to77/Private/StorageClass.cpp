// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageClass.h"
#include "TutorialWizard.h"
#include "Scrap.h"

UStorageClass::UStorageClass()
{
	ScrapInfo;

	Enemies.Empty();


}

void UStorageClass::StoreInfo(FActorInfo Info)
{

	if (Info.actorClass == AScrap::StaticClass())
	{

		ScrapInfo = Info;

	}
	else if (Info.actorClass == ATutorialWizard::StaticClass())
	{

		Enemies.Add(Info);

	}

}

void UStorageClass::StoreLevelName(FName level)
{
	PrevLevelName = level;
}

