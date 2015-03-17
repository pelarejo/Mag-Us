// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsSpell.h"
#include "Attributes.h"
#include "MagUsBuff.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsBuff : public AMagUsSpell
{
	GENERATED_BODY()
	
public:
	AMagUsBuff(const FObjectInitializer& ObjectInitializer);
	//AMagUsBuff();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UAttributes> Attr;
};
