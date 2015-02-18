// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "MagUsCharacter.generated.h"

UENUM(BlueprintType)
enum class GestEnum
{
	CIRCLE,
	SWIPE,
	KEYTAP
};

UCLASS(config=Game)
class AMagUsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMagUsCharacter(const FObjectInitializer& ObjectInitializer);
};

