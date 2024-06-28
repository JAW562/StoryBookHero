// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "ITOInter.generated.h"

/**
 * 
 */
UCLASS()
class UITOInter : public UInteractionComponent
{
	GENERATED_BODY()

public:

	UITOInter();

	virtual void OnInteractionBegin() override;

	virtual void OnInteractionEnd() override;
	
};
