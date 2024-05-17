// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Scrap.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class AScrap : public APaperCharacter
{
	GENERATED_BODY()


	/*
	* UProperty descirbes the properties of the following component. It is visble anywhere in the project, the blueprint itself can only be read and cannot be changed,
	* it's category is camers (that is more for sorting), and even though this property is declared under the private section, we want to be able to access it so we allow in blueprints
	* for it to be accessed, it is still considered private within the C++ code however. ScrapCamera inherits from UCameraComponent.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera,  meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ScrapCamera;

	/*
	* Same properties as above as the SpringArm is utilized in tandem with the camera as this is what automatically configures the camera to avoid objects
	* (Think of a platformer where the camera zooms in and out and automatically adjusts depending on what's happening, that's what this is). ScrapCameraSA inherits from spring arm 
	* component.
	*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* ScrapCameraSA;




	
};
