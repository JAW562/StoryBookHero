// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "InteractionComponent.h"
#include "Components/SphereComponent.h"
#include "Scrap.h"
#include "TutorialWizard.generated.h"

UCLASS()
class ATutorialWizard : public APaperCharacter
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = NPCs, meta = (AllowPrivateAccess = true))
	class USphereComponent* SphereCol;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = NPCs, meta = (AllowPrivateAccess = true))
	class UInteractionComponent* InterTW;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCs)
	class UPaperFlipbook* IdleAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPCs)
	class UPaperFlipbook* QuestAnim;


	UFUNCTION(BlueprintCallable, Category = NPCs)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = NPCs)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void UpdateAnim();

	UFUNCTION()
	void OnInteractionBegin();


public:	

	// Sets default values for this actor's properties
	ATutorialWizard();

	 bool scrapThere;


	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
