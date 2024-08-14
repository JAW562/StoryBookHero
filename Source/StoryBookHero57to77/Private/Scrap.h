// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ScrapInteract.h"
#include "Scrap.generated.h"

class UTextComponent;

/**
 * Our header for our scrap character, contains our camera, movement, and collision spheres.
 */ 
UCLASS(config=Game)
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* InteractSphere;

	/*
	* This is how we handle interactions in our game, if the player is within a certain radius of an interactable object and press the interact key, it will cause something to
	* happen. EditAnywhere allows us to actually make changes to it than just being able to look at it. 
	*/

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	//class USphereComponent* SphereCollision;

	/*
	* We want to use a virtual function here to override tick so we can add our own functionality to the tick fucntion which runs every frame.
	* AActor has it's own tick function but, by doing this, we have it run our tick function rather than the normal one. 
	*/

	virtual void Tick(float DeltaSeconds) override;


protected:
	/*
	* Both of these add UProperties for us to change, making them different animations that we can apply to our PaperCharacter. Paper Flipbook are animations for paper characters
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactions)
	class UScrapInteract* SIComp;



	//Our function where we will be updating the animation of our player
	void UpdateAnimation();

	//Our function for movement.
	void MoveScrap(float value);

	//Our function we use to update our players state
	void UpdateCharacter();

	void Interact();

	/*
	* This is how we setup our players input to our character. We make the arguement a pointer so we can easily setup or input component once we create it.
	*/

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 


public:

	//Constructor for AScrap, every class needs this
	AScrap();

	UPROPERTY( BlueprintReadWrite, Category = Battle)
	int Agility;

	/*
	* These are functions that have simple enough logic that we can just declare it in the header. All these do is return our created camera and camera boom.
	* FORCEINLINE makes it to whenever our function is called, the body of it is pasted instead of the body having to be retrieved from the function itself.
	* Only useful if the function is super simple. 
	*/

	FORCEINLINE class UCameraComponent* GetSideViewCamera() const { return ScrapCamera;  }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return ScrapCameraSA; }



	
};
