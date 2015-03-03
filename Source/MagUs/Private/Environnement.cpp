// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Environnement.h"
#include "Engine.h"
#include "MagUsProjectile.h"

void AEnvironnement::BeginPlay()
{
	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AEnvironnement::RegenMana, RegenRate, true);
}

void AEnvironnement::ChangeLevel(float NewMaxMana)
{
	MaxMana = NewMaxMana;
}

void AEnvironnement::RegenMana()
{
	CurrentMana += Regen;
	if (CurrentMana > MaxMana)
		CurrentMana = MaxMana;
}

bool AEnvironnement::CanCast(TSubclassOf<AMagUsSpell> Spell)
{
	return (CurrentMana >= Spell->GetDefaultObject<AMagUsProjectile>()->ManaCost);
}

void AEnvironnement::CastSpell(TSubclassOf<AMagUsSpell> Spell)
{
	CurrentMana -= Spell->GetDefaultObject<AMagUsProjectile>()->ManaCost;
}