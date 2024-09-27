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

	UFUNCTION(BlueprintCallable, Category = Combat)
	virtual void AttackCall(FActorInfo& ScrapInfo, FActorInfo& itself, bool& AFlag, bool& SFlag, bool& Wait);


	UPROPERTY(BlueprintReadWrite, Category = Combat)
	ABattleManager* TheBattleManager;

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

	UPROPERTY(BlueprintReadWrite, Category = Global)
	ASBHGameMode* GameMode;
	
	UPROPERTY(BlueprintReadWrite, Category = Global)
	UStorageClass* GameIn;

	


	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
