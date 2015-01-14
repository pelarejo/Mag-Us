// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy(const FObjectInitializer& ObjectInitializer);
};
