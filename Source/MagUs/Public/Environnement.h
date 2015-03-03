// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "MagUsSpell.h"
#include "Environnement.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MAGUS_API AEnvironnement : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float Regen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RegenRate;

public:
	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void ChangeLevel(float NewMaxMana);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	bool CanCast(TSubclassOf<AMagUsSpell> Spell);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void CastSpell(TSubclassOf<AMagUsSpell> Spell);

private:
	void RegenMana();
};
