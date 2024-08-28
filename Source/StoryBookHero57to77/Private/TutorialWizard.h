// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "InteractionComponent.h"
#include "Components/SphereComponent.h"
#include "DialogueWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "BattleManager.h"
#include "StorageClass.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	class UDialogueWidget* TWDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue)
	class UTexture2D* TWHead1;



	UFUNCTION(BlueprintCallable, Category = NPCs)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = NPCs)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void UpdateAnim();

	UFUNCTION(BlueprintCallable, Category = NPCs)
	void OnInteractionBegin();


public:	

	// Sets default values for this actor's properties
	ATutorialWizard();

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	ABattleManager* TheBattleManager;

	UFUNCTION(BlueprintCallable, Category = Battle)
	void CallBattle();

	UPROPERTY(BlueprintReadWrite, Category = Battle)
	int TWAgility;
	
	UPROPERTY(BlueprintReadWrite, Category = Interactions)
	bool scrapThere;

	UPROPERTY(BlueprintReadWrite, Category = Dialogue)
	bool dialogueMenu;

	UPROPERTY(BlueprintReadWrite, Category = Combat)
	bool combatThere;

	UPROPERTY(BlueprintReadWrite, Category = Interactions)
	AScrap* ScrapRef;

	UPROPERTY(BlueprintReadWrite, Category = Storage)
	FActorInfo NPCfo;

	


	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
