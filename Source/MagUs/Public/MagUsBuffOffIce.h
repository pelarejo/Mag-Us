// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuffOff.h"
#include "MagUsBuffOffIce.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuffOffIce : public AMagUsBuffOff
{
	GENERATED_BODY()
	
public:
	AMagUsBuffOffIce(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

private:
	void SlowCharacter();
};
