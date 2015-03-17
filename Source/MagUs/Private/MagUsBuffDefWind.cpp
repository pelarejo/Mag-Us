// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsBuffDefWind.h"

AMagUsBuffDefWind::AMagUsBuffDefWind(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Die after 10 seconds by default
	InitialLifeSpan = 10.0f;
	Type = EManaType::WIND;
}
