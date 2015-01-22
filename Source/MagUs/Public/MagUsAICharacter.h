// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MagUsAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsAICharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gameplay)
	int32 Health = 100;

public:
	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser);
};
