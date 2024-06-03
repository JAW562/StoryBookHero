#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Scrap.h"
#include "Interact.generated.h"

/**
 * 
 */

UINTERFACE(MinimalAPI)
class UInteract: public UInterface
{
	GENERATED_BODY()
};

class IInteract 
{
	GENERATED_BODY()

public:
	virtual void Interacted();

};



