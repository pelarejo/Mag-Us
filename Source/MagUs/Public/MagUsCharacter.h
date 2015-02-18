// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "MagUsCharacter.generated.h"

/* Gesture enum */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class GestEnum
{
	CIRCLE,
	SWIPE,
	KEYTAP,
	NONE
};

UCLASS(config=Game)
class AMagUsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMagUsCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = SpellManagement)
	TSubclassOf<class AMagUsProjectile> ProjectileArray[4];

};

