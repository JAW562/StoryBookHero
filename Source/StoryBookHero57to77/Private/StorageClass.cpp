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

 UPaperFlipbook* UStorageClass::GetSprite(FActorInfo Info)
 {
	 UE_LOG(LogTemp, Display, TEXT("%s"), *FString(Info.Sprite->GetName()));
	 return Info.Sprite;
 }

 UClass* UStorageClass::GetActorClass(FActorInfo Info)
 {
	 UE_LOG(LogTemp, Display, TEXT("%s"), *FString(Info.actorClass->GetName()));
	 return Info.actorClass;
 }

 int UStorageClass::GetAgility(FActorInfo Info)
 {
	 UE_LOG(LogTemp, Display, TEXT("%i"), Info.agi);
	 return Info.agi;
 }

