// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsBuffOff.h"

AMagUsBuffOff::AMagUsBuffOff(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void AMagUsBuffOff::SetTarget(AMagUsCharacter* target)
{
	Target = target;
}