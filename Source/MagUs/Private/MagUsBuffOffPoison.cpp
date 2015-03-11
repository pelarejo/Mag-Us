// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Engine.h"
#include "MagUsBuffOffPoison.h"

AMagUsBuffOffPoison::AMagUsBuffOffPoison(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	InitialLifeSpan = 10.0f;
	Type = EManaType::POISON;
}

void AMagUsBuffOffPoison::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AMagUsBuffOffPoison::PoisonCharacter, 1.0f/*Attr->GetDefaultObject<UAttributes>()->RegenerationRate*/, true);
}

void AMagUsBuffOffPoison::PoisonCharacter()
{
	if (Target)
	{
		FDamageEvent damageEvent;
		Target->ApplyDamageMomentum(1.0f/*Attr->GetDefaultObject<UAttributes>()->Strenght/Regen*/, damageEvent, this->Instigator, this);
	}
}