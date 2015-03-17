// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Engine.h"
#include "MagUsBuffOffIce.h"

AMagUsBuffOffIce::AMagUsBuffOffIce(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	InitialLifeSpan = 5.0f;
	Type = EManaType::ICE;
}

void AMagUsBuffOffIce::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AMagUsBuffOffIce::SlowCharacter, 0.5f, false);
}

void AMagUsBuffOffIce::SlowCharacter()
{
	/**
	Target->RealAttr->GetDefaultObject<UAttributes>()->Speed -= 200; //Attr->GetDefaultObject<UAttributes>()->Speed;

	// Change Speed of character
	UCharacterMovementComponent*  CharacterMovement = Target->GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = Target->RealAttr->GetDefaultObject<UAttributes>()->Speed;
	*/
}