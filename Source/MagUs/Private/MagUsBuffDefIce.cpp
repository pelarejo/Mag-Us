// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsBuffDefIce.h"

AMagUsBuffDefIce::AMagUsBuffDefIce(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Die after 3 seconds by default
	InitialLifeSpan = 10.0f;
}


