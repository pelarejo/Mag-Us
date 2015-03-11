// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuffOff.h"
#include "MagUsBuffOffPoison.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuffOffPoison : public AMagUsBuffOff
{
	GENERATED_BODY()
	
public:
	AMagUsBuffOffPoison(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

private:
	/** Apply poison damages to Character */
	void PoisonCharacter();
};
