// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageClass.h"
#include "TutorialWizard.h"
#include "Scrap.h"

UStorageClass::UStorageClass()
{
	ScrapInfo;

	Enemies.Empty();

	PC = GetWorld()->GetFirstPlayerController();


}

void UStorageClass::StoreInfo(FActorInfo Info)
{

	if (Info.actorClass == AScrap::StaticClass())
	{

		ScrapInfo = Info;

	}
	else if (Info.actorClass == ATutorialWizard::StaticClass())
	{
		if (!(Enemies.IsEmpty()))
		{
			Enemies.Empty();
		}


		Enemies.Add(Info);

	}

}

void UStorageClass::StoreLevelName(FName level)
{
	PrevLevelName = level;
}

