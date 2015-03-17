// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsCharacter.h"
#include "MagUsProjectile.h"
#include "MagUsStatSystem.h"

UMagUsStatSystem::UMagUsStatSystem(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UMagUsStatSystem::CalcDamage(AMagUsCharacter* Attacker, AMagUsCharacter* Target, AMagUsProjectile* Projectile)
{
	// Damage multiplier depending on the Type of both Characters
	float const Affinity[5][5] = {
		{ 0.5, 1.5, 1, 1, 1 },
		{ 1.5, 0.5, 1, 1, 1 },
		{ 1, 1, 0.5, 1.5, 1 },
		{ 1, 1, 1.5, 0.5, 1 },
		{ 1, 1, 1, 1, 1 }
	};

	// Get Strenght of the attacker and defense of the Target
	float AttackerStrenght = Attacker->RealAttr->GetDefaultObject<UAttributes>()->Strength;
	float TargetDefense = Target->RealAttr->GetDefaultObject<UAttributes>()->Defense;

	// Get Types of the Characters or Shield if one is attach to them
	int AttackerType = Attacker->CurrentShield ? (int)Attacker->CurrentShield->Type : (int)Attacker->Type;
	int TargetType = Target->CurrentShield ? (int)Target->CurrentShield->Type : (int)Target->Type;

	// Calc final damage
	float Damage = (AttackerStrenght - TargetDefense) * Affinity[AttackerType][TargetType];

	return Damage;
}




