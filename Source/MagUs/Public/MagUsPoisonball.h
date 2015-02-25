// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsProjectile.h"
#include "MagUsPoisonball.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsPoisonball : public AMagUsProjectile
{
	GENERATED_BODY()
	

public:
	AMagUsPoisonball(const FObjectInitializer& ObjectInitializer);
	~AMagUsPoisonball();
	
	
};
