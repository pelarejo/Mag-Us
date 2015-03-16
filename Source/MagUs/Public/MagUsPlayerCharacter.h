// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "MagUsCharacter.h"
#include "MagUsHUD.h"
#include "LeapMotionPublicPCH.h"
#include <ctime>
#include "MagUsPlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EDoubleTap : uint8
{
	DT_Init 	UMETA(DisplayName = "Initial"),
	DT_First 	UMETA(DisplayName = "First"),
	DT_Second	UMETA(DisplayName = "Second"),
	DT_Reset	UMETA(DisplayName = "Reset")
};

UCLASS(config = Game)
class AMagUsPlayerCharacter : public AMagUsCharacter
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 LockMaxDistance;

	/** This should be used for HMD confort */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 LockMinDistance;

	clock_t last = clock();
	bool canAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=SpellManagement)
	GestEnum spellType;

protected:
	static const float DoubleTapResetTime_CST;
	static const float DashForce_CST;

	// LockedActor is linked to the in-game mode
	AActor* LockedActor;
	// bLockedPressed is linked to input
	bool	bLockedPressed;

	EDoubleTap	DoubleTap;

	bool		bSignX; // true = negative

	bool		bShieldMode;

	/** Fires a projectile. */
	void ShieldOrFire();
	void OnFire();

	/** Launch a shield. */
	void ShieldModeOn();
	void ShieldModeOff();
	void LaunchShield();

	/** Locks on enemy */
	void LockPressed();
	void LockReleased();
	void OnLock();
	void OffLock();
	void InLock_Tick(float DeltaSeconds);

	/** Get gesture type **/
	UFUNCTION(BlueprintCallable, Category = "SpellManagement")
	GestEnum getGestureType(FString gest);

	void RefreshCanAttack();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	FORCEINLINE void MoveRight(float Val);
	void MoveRight(float Val, bool bAnalog);

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

	void ResetHMD();
	void ToggleMenu();
	void MenuClick();

	bool DoubleTapDigital(float Value);
	bool DoubleTapAnalog(float Rate);
	void Dash(float Multiplier);

	void RegenPlayer();

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

	virtual void BeginPlay() override;

private:
	FORCEINLINE void Timer_DoubleTapReset();
//
	UClass		*UCMagUsController;
	bool		isMenuOpen;
};

