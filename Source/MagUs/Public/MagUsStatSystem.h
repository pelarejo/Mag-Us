// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "MagUsStatSystem.generated.h"

class AMagUsCharacter;
class AMagUsProjectile;

/**
 * Classe implémentant toutes les formules de gameplay
 */
UCLASS()
class MAGUS_API UMagUsStatSystem : public UObject
{
	GENERATED_BODY()
	
public:
	UMagUsStatSystem(const FObjectInitializer& ObjectInitializer);

	static float CalcDamage(AMagUsCharacter* Attacker, AMagUsCharacter* Target, AMagUsProjectile* Projectile);

};
