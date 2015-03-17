// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "Attributes.h"
#include "MagUsBuffDef.h"
#include "Enums.h"
#include "MagUsCharacter.generated.h"



class AMagUsBuffOff;

UCLASS(config=Game)
class AMagUsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMagUsCharacter(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void RemoveDebuff(AMagUsBuffOff* debuff);

	void AddDebuff(AMagUsBuffOff* debuff);

protected:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = SpellManagement)
	TSubclassOf<class AMagUsProjectile> ProjectileArray[4];

	/** Shield class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = SpellManagement)
	TSubclassOf<class AMagUsBuffDef> ShieldArray[4];

	/** Array of Debuff in the Character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SpellManagement)
	TArray<AMagUsBuffOff*> Debuffs;


	/** Location for projectiles to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ProjectileOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimSequence* FireAnimation2;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UAttributes> BaseAttr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UAttributes> RealAttr;

	/** Current Shield on Character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	AMagUsBuffDef* CurrentShield = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpellManagement)
	EManaType Type = EManaType::NONE;
};

