// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enums.h"
#include "MagUsSpell.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsSpell : public AActor
{
	GENERATED_BODY()
	
public:
	AMagUsSpell(const FObjectInitializer& ObjectInitializer);
	//AMagUsSpell();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	float ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	EManaType Type;
};
