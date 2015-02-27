// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsBuffDef.h"


AMagUsBuffDef::AMagUsBuffDef(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
//	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

//AMagUsBuffDef::AMagUsBuffDef()
//	: Super()
//{
//	// Die after 3 seconds by default
//	InitialLifeSpan = 3.0f;
//}

