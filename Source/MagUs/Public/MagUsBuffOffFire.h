// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuffOff.h"
#include "MagUsCharacter.h"
#include "MagUsBuffOffFire.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuffOffFire : public AMagUsBuffOff
{
	GENERATED_BODY()
	
public:
	AMagUsBuffOffFire(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

private:
	/** Apply burn damages to Character */
	void BurnCharacter();
};
