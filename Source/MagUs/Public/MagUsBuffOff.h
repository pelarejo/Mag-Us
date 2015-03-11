// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuff.h"
#include "MagUsCharacter.h"
#include "MagUsBuffOff.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuffOff : public AMagUsBuff
{
	GENERATED_BODY()
	
public:
	AMagUsBuffOff(const FObjectInitializer& ObjectInitializer);

	void SetTarget(AMagUsCharacter* target);

protected:
	/** Target of the Debuf */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	AMagUsCharacter* Target;
};
