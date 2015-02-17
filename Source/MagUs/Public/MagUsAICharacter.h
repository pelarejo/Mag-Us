// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MagUsAICharacter.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class MAGUS_API AMagUsAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser);

protected:
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void OnFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Strength = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Defense = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Regeneration = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RegenerationRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Speed = 600;
};
