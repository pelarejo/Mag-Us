// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuffOff.h"
#include "MagUsBuffOffWind.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuffOffWind : public AMagUsBuffOff
{
	GENERATED_BODY()
	
public:
	AMagUsBuffOffWind(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
};
