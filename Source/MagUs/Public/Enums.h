// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enums.generated.h"

/* Gesture enum */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class GestEnum : uint8
{
	CIRCLE = 0,
	SWIPE = 1,
	KEYTAP = 2,
	NONE = 3
};

/* Mana Type enum */
UENUM(BlueprintType)
enum class EManaType : uint8
{
	FIRE = 0, // CIRCLE
	ICE = 1, // SWIPE
	POISON = 2, // KEYTAP
	WIND = 3, // NONE
	NONE = 4
};