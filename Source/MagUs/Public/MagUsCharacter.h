// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "GameFramework/Character.h"
#include "Attributes.h"
#include "Environnement.h"
#include "MagUsBuffDef.h"
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

	/** Shield class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = SpellManagement)
	TSubclassOf<class AMagUsBuffDef> ShieldArray[4];

	/** Location for projectiles to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector ProjectileOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UAttributes> BaseAttr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TSubclassOf<class UAttributes> RealAttr;

	UPROPERTY()
	AEnvironnement* ManaPool;

public:
	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	void setManaPool(AEnvironnement* mana_pool);

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	AEnvironnement* getManaPool();
};

