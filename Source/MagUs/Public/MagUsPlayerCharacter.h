// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "MagUsHUD.h"
#include "LeapMotionPublicPCH.h"
#include <ctime>
#include <iostream>
#include "MagUsCharacter.h" // For enum
#include "MagUsPlayerCharacter.generated.h"

UCLASS(config=Game)
class AMagUsPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	AMagUsPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AMagUsProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 LockMaxDistance;

	/** This should be used for HMD confort */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 LockMinDistance;

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

	clock_t last = clock();

protected:
	// LockedActor is linked to the in-game mode
	AActor* LockedActor;
	// bLockedPressed is linked to input
	bool	bLockedPressed;

	/** Fires a projectile. */
	void OnFire();

	/** Locks on enemy */
	void LockPressed();
	void LockReleased();
	void OnLock();
	void OffLock();
	void InLock_Tick(float DeltaSeconds);

	/** Get gesture type **/
	UFUNCTION(BlueprintCallable, Category = "SpellManagement")
	GestEnum getGestureType(FString gest);

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void TurnRateOrMoveRight(float Value);

	bool IsLockedActorInFrustum(const float FOVAngle, const float DeltaSeconds);
	bool IsLockedActorWithinDistance();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick(float DeltaSeconds) override;

	virtual void AddControllerYawInput(float Val) override;

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Apply damage to character */
	virtual void ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser);

	virtual void Killed(AActor* Someone);

};

