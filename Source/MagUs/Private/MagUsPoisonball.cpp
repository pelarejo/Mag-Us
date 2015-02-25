// Fill out your copyright notPoison in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsPoisonball.h"


AMagUsPoisonball::AMagUsPoisonball(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Poisonball's damage
	SetDamage(20000000000.0f);
}


AMagUsPoisonball::~AMagUsPoisonball()
{
}

