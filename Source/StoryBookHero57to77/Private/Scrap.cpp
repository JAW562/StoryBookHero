// Fill out your copyright notice in the Description page of Project Settings.


#include "Scrap.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/InputComponent.h"


/*
* This line defines what gets logged by VS's logs whenver an error happens. We make it static so AScrap logs only appear here and nowhere else, AScrap is the category, Log is all general information
* there are other levels that can be put here. All is the level of verbosity of the errors, so All allows any.
*/


DEFINE_LOG_CATEGORY_STATIC(AScrap, Log, All)

//:: is a scope resolution operator, it has many uses, in this case it seperates the class from the constructor. 
AScrap::AScrap() 
{
	//b is always put in front of booleans. We only use Yaw for our 2D game as this lets us rotate our 2D Character from side to side.
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//Sets the height and width of the capsule around our character
	GetCapsuleComponent()->SetCapsuleHalfHeight(56.0f);
	GetCapsuleComponent()->SetCapsuleRadius(20.0f);

	//We set up our spring arm here.
	ScrapCameraSA = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	//Attaches the spring arm to the root component of Scrap
	ScrapCameraSA->SetupAttachment(RootComponent);

	//The arm length of our Camera Boom
	ScrapCameraSA->TargetArmLength = 500.0f;

	//We want the socket offset of our camera to be on the z axis so we set can attach our camera at the right point.
	ScrapCameraSA->SocketOffset = FVector(0.0f, 0.0f, 75.0f);

	//Set the rotation of our Camera Boom to use absolute instead of relative. Relative is relative to the parent, which is the root component, Absolute is to the world.
	ScrapCameraSA->SetUsingAbsoluteRotation(true);

	//This prevents our camrea boom from going through a collision test to see if it is clipping with anything, this also stops it from automatically adjusting if it is. Let's just avoid doing that
	ScrapCameraSA->bDoCollisionTest = false;

	//Set our camera boom so it faces our character. Normally SetRotations use a FQuat which is Quaternion. But we use Rotator as we are doing 2D
	ScrapCameraSA->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	//Sets up our Camera itself.
	ScrapCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//Sets our cameras projection mode to orthographic rather than perspective as we do not need to handle depth with our 2D game.
	ScrapCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	//Stes the width of the orthographic 
	ScrapCamera->SetOrthoWidth(500.0f);
	
	//Attaches our camera to the socket of our spring arm. Anytime you setup attachment, you can provide it with a socket to attach to.
	ScrapCamera->SetupAttachment(ScrapCameraSA, USpringArmComponent::SocketName);

	//Since our cammera is now attached to our spring arm, we add another check so the camera operates on the same absolute rotation,
	ScrapCameraSA->SetUsingAbsoluteRotation(true);

	//Makes sure our camera does not use the players controller rotation.
	ScrapCamera->bUsePawnControlRotation = false;

	//Camera auto activates on creation.
	ScrapCamera->bAutoActivate = true;

	InteractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction"));

	InteractSphere->SetSphereRadius(40.0f);

	//This is so our character does not orient toward the controllers rotation. Essential for our character to always remain visbile in our 2D game. 
	GetCharacterMovement()->bOrientRotationToMovement = false;

	//Sets the gravity our character will adhere to.
	GetCharacterMovement()->GravityScale = 2.0f;

	//Sets how much control our character has in the air.
	GetCharacterMovement()->AirControl = 0.80f;

	//Launch velocity with jump
	GetCharacterMovement()->JumpZVelocity = 1000.0f;

	//Friction for player on ground.
	GetCharacterMovement()->GroundFriction = 3.0f;

	//Max walk speed
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;

	//Max fly speed, if ever applicable.
	GetCharacterMovement()->MaxFlySpeed = 300.0f;

	//First you need to set the constrain to plane to be true, then you tell the engine which plane to use.
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	//For some reason this isn't under capsule component, makes the capsule component register as a flat base with floors so platforming is smoother.
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;


	

}

void AScrap::UpdateAnimation()
{
	//Gets the current velocity of our character, we make it a constant so it does not change during the course of executing this function.
	const FVector currentVelocity = GetVelocity();

	//We square the size of our vector to get a single float value.
	const float fVelocity = currentVelocity.SizeSquared();

	//We creeate a new curAnimatiuon class to store our current animation
	//UPaperFlipbook* curAnimation;

	//If check to see which current animation we are on, running or idle. Base it off of our current velocity
	//if (fVelocity > 0.0f)
	//{
		//curAnimation = RunningAnimation;
	//}
	//else
	//{
		//curAnimation = IdleAnimation;
	//}

	//Better way to do what I descibed above, we use the conditional operator instead.
	UPaperFlipbook* curAnimation = (fVelocity > 0.0f) ? RunningAnimation : IdleAnimation;
	
	//Check to see if current sprite flipbook is executing our desired animation, if not, we make sure it s.
	if (GetSprite()->GetFlipbook() != curAnimation)
	{
		GetSprite()->SetFlipbook(curAnimation);
	}


}

//Definintion for our Tick function
void AScrap::Tick(float DeltaSeconds)
{
	//We use a super class in order to call the tick fucntion from APaperCharacter here. Basically all our function does is call tick along with update character
	Super::Tick(DeltaSeconds);

	UpdateCharacter();
}

//Definition for our SetupPlayerInputComponent, which includes binding jump and movement
void AScrap::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//We set up our input components here. Binding actions for Jump and binding Axis for Move right.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AScrap::MoveScrap);

}

//Our function for moving Scrap
void AScrap::MoveScrap(float value)
{
	//Call add movement input and pass our direction vector, only being x so we only move along the x plane
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
}

//The function to be called along with Tick in order to provide accurate character infromation
void AScrap::UpdateCharacter()
{
	//Makes sure our characters animation is up to date
	UpdateAnimation();

	//Gets our characters current velocity so we can then see their current direction. 
	const FVector curVelocity = GetVelocity();
	float travelDirection = curVelocity.X;

	//Checks if we have a controller
	if (Controller !=nullptr)
	{
		//Check to see if player is traveling left
		if (travelDirection < 0.0f)
		{
			//Set so controller moves player left
			Controller->SetControlRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		//Check to see if player is traveling right
		else if (travelDirection > 0.0f)
		{
			//Set so controller moves player right
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

}