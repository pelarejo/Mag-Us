// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Attributes.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MAGUS_API UAttributes : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Strength = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Defense = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Regeneration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RegenerationRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Speed = 0;
};
