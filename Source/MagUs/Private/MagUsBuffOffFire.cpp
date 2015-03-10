// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Engine.h"
#include "MagUsBuffOffFire.h"

AMagUsBuffOffFire::AMagUsBuffOffFire(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InitialLifeSpan = 5.0f;
}

void AMagUsBuffOffFire::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AMagUsBuffOffFire::BurnCharacter, 1.0f/*Attr->GetDefaultObject<UAttributes>()->RegenerationRate*/, true);
}

void AMagUsBuffOffFire::BurnCharacter()
{
	if (Target)
	{
		FDamageEvent damageEvent;
		Target->ApplyDamageMomentum(2.0f/*Attr->GetDefaultObject<UAttributes>()->Strenght/Regen*/, damageEvent, this->Instigator, this);
	}
}