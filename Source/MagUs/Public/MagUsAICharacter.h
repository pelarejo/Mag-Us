// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsCharacter.h"
#include "MagUsAICharacter.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class MAGUS_API AMagUsAICharacter : public AMagUsCharacter
{
	GENERATED_BODY()

public:
	AMagUsAICharacter(const FObjectInitializer& ObjectInitializer);

	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser);

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpellManagement)
	GestEnum spellType;
protected:
	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void OnFire();

	UFUNCTION(BlueprintCallable, Category = "SpellManagement")
	void setSpellType(int32 newValue);

};
