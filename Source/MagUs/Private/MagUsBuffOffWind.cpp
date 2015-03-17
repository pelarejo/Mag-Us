// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsBuffOffWind.h"

AMagUsBuffOffWind::AMagUsBuffOffWind(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	InitialLifeSpan = 5.0f;
	Type = EManaType::WIND;
}

void AMagUsBuffOffWind::BeginPlay()
{
	Super::BeginPlay();
}