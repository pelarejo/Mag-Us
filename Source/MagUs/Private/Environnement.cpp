// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Environnement.h"
#include "Engine.h"
#include "MagUsProjectile.h"

void AEnvironnement::BeginPlay()
{
	Regen.Init(4);
	Regen[(int)EManaType::FIRE] = MaxMana[(int)EManaType::FIRE] * RegenPercent;
	Regen[(int)EManaType::ICE] = MaxMana[(int)EManaType::ICE] * RegenPercent;
	Regen[(int)EManaType::POISON] = MaxMana[(int)EManaType::POISON] * RegenPercent;
	Regen[(int)EManaType::WIND] = MaxMana[(int)EManaType::WIND] * RegenPercent;

	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AEnvironnement::RegenMana, RegenRate, true);
}

void AEnvironnement::ChangeLevel(TArray<float> NewMaxMana)
{
	CurrentMana[(int)EManaType::FIRE] = MaxMana[(int)EManaType::FIRE] = NewMaxMana[(int)EManaType::FIRE];
	CurrentMana[(int)EManaType::ICE] = MaxMana[(int)EManaType::ICE] = NewMaxMana[(int)EManaType::ICE];
	CurrentMana[(int)EManaType::POISON] = MaxMana[(int)EManaType::POISON] = NewMaxMana[(int)EManaType::POISON];
	CurrentMana[(int)EManaType::WIND] = MaxMana[(int)EManaType::WIND] = NewMaxMana[(int)EManaType::WIND];

	Regen[(int)EManaType::FIRE] = MaxMana[(int)EManaType::FIRE] * RegenPercent;
	Regen[(int)EManaType::ICE] = MaxMana[(int)EManaType::ICE] * RegenPercent;
	Regen[(int)EManaType::POISON] = MaxMana[(int)EManaType::POISON] * RegenPercent;
	Regen[(int)EManaType::WIND] = MaxMana[(int)EManaType::WIND] * RegenPercent;
}

void AEnvironnement::RegenMana()
{
	float diffFire = MaxMana[(int)EManaType::FIRE] - CurrentMana[(int)EManaType::FIRE];
	float diffIce = MaxMana[(int)EManaType::ICE] - CurrentMana[(int)EManaType::ICE];
	float diffPoison = MaxMana[(int)EManaType::POISON] - CurrentMana[(int)EManaType::POISON];
	float diffWind = MaxMana[(int)EManaType::WIND] - CurrentMana[(int)EManaType::WIND];

	CurrentMana[(int)EManaType::FIRE] += MIN(diffFire, Regen[(int)EManaType::FIRE]);
	CurrentMana[(int)EManaType::ICE] += MIN(diffIce, Regen[(int)EManaType::ICE]);
	CurrentMana[(int)EManaType::POISON] += MIN(diffPoison, Regen[(int)EManaType::POISON]);
	CurrentMana[(int)EManaType::WIND] += MIN(diffWind, Regen[(int)EManaType::WIND]);
}

bool AEnvironnement::CanCast(TSubclassOf<AMagUsSpell> Spell)
{
	/** Type of the Spell */
	EManaType Type = Spell->GetDefaultObject<AMagUsProjectile>()->Type;

	return (CurrentMana[(int)Type] >= Spell->GetDefaultObject<AMagUsProjectile>()->ManaCost);
}

void AEnvironnement::CastSpell(TSubclassOf<AMagUsSpell> Spell)
{
	/** Type of the Spell */
	EManaType Type = Spell->GetDefaultObject<AMagUsProjectile>()->Type;

	CurrentMana[(int)Type] -= Spell->GetDefaultObject<AMagUsProjectile>()->ManaCost;
}