// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuff.h"
#include "MagUsBuffDef.generated.h"

/**
 * Base des buffs défensifs, à renommer en AMagUsShield ?
 */
UCLASS()
class MAGUS_API AMagUsBuffDef : public AMagUsBuff
{
	GENERATED_BODY()

public:
	AMagUsBuffDef(const FObjectInitializer& ObjectInitializer);

};
