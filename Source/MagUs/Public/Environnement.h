// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "MagUsSpell.h"
#include "Environnement.generated.h"

#define  MIN(a,b) ((a) < (b) ? (a) : (b))

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MAGUS_API AEnvironnement : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	TArray<float> MaxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	TArray<float> CurrentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	float RegenPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	float RegenRate;

public:
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void ChangeLevel(TArray<float> NewMaxMana);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	bool CanCast(TSubclassOf<AMagUsSpell> Spell);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void CastSpell(TSubclassOf<AMagUsSpell> Spell);

private:
	TArray<float> Regen;

	void RegenMana();
};
