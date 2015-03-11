// Fill out your copyright notice in the Description page of Project Settings.
#include "MagUs.h"
#include "MagUsBuffOff.h"
#include "MagUsCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AMagUsCharacter

AMagUsCharacter::AMagUsCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void AMagUsCharacter::AddDebuff(AMagUsBuffOff* debuff)
{
	Debuffs.Push(debuff);
}

void AMagUsCharacter::RemoveDebuff(AMagUsBuffOff* debuff)
{
	Debuffs.Push(debuff);
}