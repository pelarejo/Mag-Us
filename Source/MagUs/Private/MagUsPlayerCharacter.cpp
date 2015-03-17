// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "LeapMotionPublicPCH.h"
#include "MagUsPlayerCharacter.h"
#include "MagUsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Engine.h"
#include "math.h"
#include <iostream>
#include "HeadMountedDisplay.h"
#include "Environnement.h"
#include "MagUsGameMode.h"
#include "MagUsPlayerController.h"

//////////////////////////////////////////////////////////////////////////
// AMagUsPlayerCharacter

const float AMagUsPlayerCharacter::DoubleTapResetTime_CST = 0.2f;
const float AMagUsPlayerCharacter::DashForce_CST = 2000.0f;

AMagUsPlayerCharacter::AMagUsPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	ProjectileOffset = FVector(60.0f, 0.0f, 0.0f);

	/*// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;*/

	// Default Lock Distance (Random values, they are set in BP)
	LockMaxDistance = 2500;
	LockMinDistance = 200;

	LockedActor = NULL;
	bLockedPressed = false;
	bShieldMode = false;
	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	this->canAttack = true;


	//To get function for blueprint
	static ConstructorHelpers::FObjectFinder<UBlueprint> BPMagUsController(TEXT("Blueprint'/Game/Blueprints/MagUsController_BP.MagUsController_BP'"));
	if (BPMagUsController.Object != NULL)
	{
		UCMagUsController = Cast<UClass>(BPMagUsController.Object->GeneratedClass);
	}
	isMenuOpen = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMagUsPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	// Actions
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMagUsPlayerCharacter::ShieldOrFire);
	InputComponent->BindAction("Shield", IE_Pressed, this, &AMagUsPlayerCharacter::ShieldModeOn);
	InputComponent->BindAction("Shield", IE_Released, this, &AMagUsPlayerCharacter::ShieldModeOff);

	InputComponent->BindAction("Lock", IE_Pressed, this, &AMagUsPlayerCharacter::LockPressed);
	InputComponent->BindAction("Lock", IE_Released, this, &AMagUsPlayerCharacter::LockReleased);

	InputComponent->BindAction("ResetHMDPosition", IE_Pressed, this, &AMagUsPlayerCharacter::ResetHMD);
	InputComponent->BindAction("ToggleMenu", IE_Pressed, this, &AMagUsPlayerCharacter::ToggleMenu);

	// Axis
	InputComponent->BindAxis("MoveForward", this, &AMagUsPlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMagUsPlayerCharacter::MoveRight);

	/// Mouse
	InputComponent->BindAxis("Turn", this, &AMagUsPlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	/// Controller
	InputComponent->BindAxis("TurnRate", this, &AMagUsPlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUpRate", this, &AMagUsPlayerCharacter::LookUpAtRate);
	InputComponent->BindAxis("TurnRateOrMoveRight", this, &AMagUsPlayerCharacter::TurnRateOrMoveRight);
}

void AMagUsPlayerCharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	Health -= DamageTaken; // TODO : Calc the DamageTaken
}

void AMagUsPlayerCharacter::ShieldOrFire() {
	if (bShieldMode == false) {
		OnFire();
	}
	else {
		LaunchShield();
	}
}

void AMagUsPlayerCharacter::OnFire()
{
	// Get the right Spell to cast
	TSubclassOf<class AMagUsProjectile> Spell = ProjectileArray[(int)this->spellType];

	// Get the World
	UWorld* const World = GetWorld();
	if (!World)
		return;
	
	// Get the ManaPool from MagUsGameMode
	AMagUsGameMode * GameMode = (AMagUsGameMode*)World->GetAuthGameMode();
	AEnvironnement* ManaPool = GameMode->getManaPool();

	// Check if the Spell can be cast
	if (Spell && ManaPool && ManaPool->CanCast(Spell))
	{
		FRotator SpawnRotation = GetControlRotation();

		// SpawnOffset is in camera space, so transform it to world space before offsetting from the character location to find the final spawn position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileOffset);
		if (LockedActor == NULL && GEngine->IsStereoscopic3D()) {
			AMagUsPlayerController* PC = Cast<AMagUsPlayerController>(GetController());
			SpawnRotation = PC->PlayerCameraManager->GetActorForwardVector().Rotation();
		}

		// Set the instigator of the spell
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Cast and spawn the spell
		ManaPool->CastSpell(Spell);
		AMagUsProjectile* Projectile = World->SpawnActor<AMagUsProjectile>(Spell, SpawnLocation, SpawnRotation, SpawnParams);
		//Projectile->SetDamage(RealAttr->GetDefaultObject<UAttributes>()->Strength); // For now, will be replaced by damage calc in Projectile

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void AMagUsPlayerCharacter::ShieldModeOn() {
	bShieldMode = true;
}

void AMagUsPlayerCharacter::ShieldModeOff() {
	bShieldMode = false;
}

void AMagUsPlayerCharacter::LaunchShield()
{
	// Get the right Spell to cast
	TSubclassOf<class AMagUsBuffDef> Spell = ShieldArray[(int)this->spellType];

	// Get the World
	UWorld* const World = GetWorld();
	if (!World)
		return;

	// Get the ManaPool from MagUsGameMode
	AMagUsGameMode * GameMode = (AMagUsGameMode*)World->GetAuthGameMode();
	AEnvironnement* ManaPool = GameMode->getManaPool();

	// Check if the Spell can be cast
	if (Spell && ManaPool && ManaPool->CanCast(Spell))
	{
		FRotator SpawnRotation = GetControlRotation();

		// SpawnOffset is in camera space, so transform it to world space before offsetting from the character location to find the final spawn position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileOffset);

		FVector SocketLocationR;
		SocketLocationR = GetMesh()->GetSocketLocation("WeaponR");

		// Set the instigator of the spell
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Cast and spawn the spell
		ManaPool->CastSpell(Spell);
		AMagUsBuffDef* Shield = World->SpawnActor<AMagUsBuffDef>(Spell, SocketLocationR, SpawnRotation, SpawnParams);
		Shield->AttachRootComponentTo(GetMesh(), FName(TEXT("WeaponPoint")), EAttachLocation::SnapToTarget); // Attach the root component of our Weapon actor to the ArmMesh at the location of the socket.

		//TODO : faire les init liés au Shield

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
	}
}

void AMagUsPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

// FORCEINLINE function, it's for Digital/Analog Overload - Do not add stuff here
void AMagUsPlayerCharacter::MoveRight(float Value)
{
	MoveRight(Value, false);
}

void AMagUsPlayerCharacter::MoveRight(float Value, bool bAnalog)
{
	(bAnalog == false) ? DoubleTapDigital(Value) : DoubleTapAnalog(Value);
	if (Value != 0.0f) {
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMagUsPlayerCharacter::AddControllerYawInput(float Val) {
	//Disable manual rotation when in locked mode
	if (LockedActor == NULL) {
		Super::AddControllerYawInput(Val);
	}
}

void AMagUsPlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	DoubleTapAnalog(Rate);
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMagUsPlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMagUsPlayerCharacter::TurnRateOrMoveRight(float Value) {
	(bLockedPressed == false) ? TurnAtRate(Value) : MoveRight(Value, true);
}

bool AMagUsPlayerCharacter::DoubleTapDigital(float Value) {
	// Resets DT when switching side
	if (Value != 0.0f && (Value < 0.0f) != bSignX) {
		if (DoubleTap == EDoubleTap::DT_Second)
			GetWorldTimerManager().ClearTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset);
		DoubleTap = EDoubleTap::DT_Init;
		bSignX = (Value < 0.0f);
	}
	// Actual DT detection
	switch (DoubleTap) {
	case EDoubleTap::DT_Init:
		if (abs(Value) == 1.0f) {
			DoubleTap = EDoubleTap::DT_First;
			GetWorldTimerManager().SetTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset, DoubleTapResetTime_CST, false);
		}
		break;
	case EDoubleTap::DT_First:
		if (abs(Value) == 0.0f)
			DoubleTap = EDoubleTap::DT_Second;
		break;
	case EDoubleTap::DT_Second:
		if (abs(Value) == 1.0f) {
			Dash(Value);
			GetWorldTimerManager().ClearTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset);
			Timer_DoubleTapReset();
			return true;
		}
		break;
	case EDoubleTap::DT_Reset:
		if (abs(Value) == 0.0f)
			DoubleTap = EDoubleTap::DT_Init;
		break;
	default:
		break;
	}
	return false;
}

bool AMagUsPlayerCharacter::DoubleTapAnalog(float Rate) {
	float Threashold = 0.8f;
	float Zero = 0.4f;

	if (bLockedPressed == false || abs(Rate) < Zero)
		return false;
	// Resets DT when switching side
	if (abs(Rate) > Zero && (Rate < 0.0f) != bSignX) {
		if (DoubleTap == EDoubleTap::DT_Second)
			GetWorldTimerManager().ClearTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset);
		DoubleTap = EDoubleTap::DT_Init;
		bSignX = (Rate < 0.0f);
	}
	// Actual DT detection
	switch (DoubleTap) {
	case EDoubleTap::DT_Init:
		if (abs(Rate) > Threashold) {
			DoubleTap = EDoubleTap::DT_First;
			GetWorldTimerManager().SetTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset, DoubleTapResetTime_CST, false);
		}
		break;
	case EDoubleTap::DT_First:
		if (abs(Rate) > Zero && abs(Rate) < Threashold)
			DoubleTap = EDoubleTap::DT_Second;
		break;
	case EDoubleTap::DT_Second:
		if (abs(Rate) > Threashold) {
			Dash((Rate < 0.0f) ? -1 : 1);
			GetWorldTimerManager().ClearTimer(this, &AMagUsPlayerCharacter::Timer_DoubleTapReset);
			Timer_DoubleTapReset();
			return true;
		}
		break;
	case EDoubleTap::DT_Reset:
		if (abs(Rate) > Zero && abs(Rate) < Threashold)
			DoubleTap = EDoubleTap::DT_Init;
		break;
	default:
		break;
	}
	return false;
}

void AMagUsPlayerCharacter::Dash(float Multiplier) {
	FVector DashVect(0, Multiplier * DashForce_CST, 0);
	DashVect = FRotator(0, GetControlRotation().Yaw, 0).RotateVector(DashVect);
	LaunchCharacter(DashVect, false, true);
}

void AMagUsPlayerCharacter::ResetHMD() {
	if (GEngine->HMDDevice.IsValid() && GEngine->IsStereoscopic3D())
	{
		GEngine->HMDDevice->ResetOrientationAndPosition(0.0f);
	}
}

void AMagUsPlayerCharacter::MenuClick() {
	AMagUsPlayerController* PC = Cast<AMagUsPlayerController>(GetController());
	check(PC);
	FInteractive Inter = PC->TraceFromCamera(ECC_Pawn);
	if (Inter.bHitInteractive == true)
	{
		if (UCMagUsController)
		{
			UFunction *func = UCMagUsController->FindFunctionByName("MenuClick");
			if (func != NULL)
			{
				AMagUsPlayerController* PC = Cast<AMagUsPlayerController>(GetController());
				FString sname = Inter.Component->GetFName().GetPlainNameString();
				PC->ProcessEvent(func, &sname);
			}
		}
	}
}

void AMagUsPlayerCharacter::ToggleMenu() {
	if (UCMagUsController)
	{
		UFunction *func = UCMagUsController->FindFunctionByName("ToggleMenu");
		if (func != NULL)
		{
			AMagUsPlayerController* PC = Cast<AMagUsPlayerController>(GetController());
			PC->ProcessEvent(func, NULL);
			isMenuOpen = true;
		}
	}
}

void AMagUsPlayerCharacter::LockPressed() {
	if (isMenuOpen == true)
		MenuClick();
	else
	{
		bLockedPressed = true;
		OnLock();
	}
}

void AMagUsPlayerCharacter::LockReleased() {
	bLockedPressed = false;
	OffLock();
}

void AMagUsPlayerCharacter::OnLock() {
	AMagUsPlayerController* PC = Cast<AMagUsPlayerController>(GetController());
	check(PC);
	FInteractive Inter = PC->TraceFromCamera(ECC_Pawn);
		if (Inter.Actor != NULL) {
			LockedActor = Inter.Actor;
		}
}

void AMagUsPlayerCharacter::OffLock() {
	if (LockedActor == NULL)
		return;
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Unlocking " + LockedActor->GetName());
	LockedActor = NULL;
	APlayerController* PC = Cast<APlayerController>(GetController());
	check(PC);
	AMagUsHUD* CharacterHUD = Cast<AMagUsHUD>(PC->GetHUD());
	check(CharacterHUD);
	CharacterHUD->ResetDefaultCrosshairPosition();
}

void AMagUsPlayerCharacter::InLock_Tick(float DeltaSeconds) {
	APlayerController* PC = Cast<APlayerController>(GetController());
	check(PC);
	// Detect if LockedActor not hidden behind object, not too far and still in frustum
	if (LockedActor != NULL
		&& PC->LineOfSightTo(LockedActor) == true
		&& IsLockedActorWithinDistance() == true
		&& IsLockedActorInFrustum(PC->PlayerCameraManager->GetFOVAngle(), DeltaSeconds)) {
		// Move HUD
		AMagUsHUD* CharacterHUD = Cast<AMagUsHUD>(PC->GetHUD());
		check(CharacterHUD);
		CharacterHUD->SetCrosshairPosition(LockedActor->GetActorLocation());

		// Face LockedActor
		FRotator Rot = FRotationMatrix::MakeFromX(LockedActor->GetActorLocation() - this->GetActorLocation()).Rotator();
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Rotating" + FString::SanitizeFloat(Rot.Yaw));
		GetController()->SetControlRotation(Rot);
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Losing lock");
		OffLock();
	}
}

void AMagUsPlayerCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (LockedActor != NULL) {
		InLock_Tick(DeltaSeconds);
	}
}

// Detect if out of camera view using angle && render time (* 2 for float margin of error)
bool AMagUsPlayerCharacter::IsLockedActorInFrustum(const float FOVAngle, const float DeltaSeconds) {
	check(FirstPersonCameraComponent);
	if (LockedActor == NULL)
		return false;

	FVector PlayerToLockedActor(LockedActor->GetActorLocation() - FirstPersonCameraComponent->GetComponentLocation());
	PlayerToLockedActor.Normalize();

	const float dot = FVector::DotProduct(PlayerToLockedActor, FirstPersonCameraComponent->GetForwardVector());
	const float LockedActorAngle = FMath::RadiansToDegrees(acos(dot));
	if (LockedActorAngle > FOVAngle / 2) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Angle Disconect");
		return false;
	}
	// Works on good pc but doesn't on weak laptop
	//if (GetWorld()->TimeSeconds - LockedActor->GetLastRenderTime() > DeltaSeconds * 2) {
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Render Disconect");
	//	return false;
	//}
	return true;
}

bool AMagUsPlayerCharacter::IsLockedActorWithinDistance() {
	if (LockedActor == NULL)
		return false;

	FVector This_LockedActorVec = this->GetActorLocation() - LockedActor->GetActorLocation();
	if (This_LockedActorVec.Size() > LockMaxDistance
		|| This_LockedActorVec.Size() < LockMinDistance) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Distance Disconect");
		return false;
	}
	return true;
}

void AMagUsPlayerCharacter::Killed(AActor* Someone) {
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, Someone->GetName());
	if (Someone == LockedActor) {
		OffLock();
	}
}

void AMagUsPlayerCharacter::RefreshCanAttack()
{
	this->canAttack = true;
}

GestEnum AMagUsPlayerCharacter::getGestureType(FString gest)
{
	if (this->canAttack == true)
	{
		GetWorldTimerManager().SetTimer(this, &AMagUsPlayerCharacter::RefreshCanAttack, 0.2f, true);
		this->canAttack = false;
		if (gest == "Circle")
		{
			this->spellType = GestEnum::CIRCLE;
			if (bShieldMode == true) {
				LaunchShield();
			}
			else {
				this->OnFire();
			}
			return GestEnum::CIRCLE;
		}
		else if (gest == "KeyTap")
		{
			this->spellType = GestEnum::KEYTAP;
			if (bShieldMode == true) {
				LaunchShield();
			}
			else {
				this->OnFire();
			}
			return GestEnum::KEYTAP;
		}
		else if (gest == "Swipe")
		{
			this->spellType = GestEnum::SWIPE;
			if (bShieldMode == true) {
				LaunchShield();
			}
			else {
				this->OnFire();
			}
			return GestEnum::SWIPE;
		}
		else if (gest == "POISON")
		{
			this->spellType = GestEnum::LEFTHAND;
			if (bShieldMode == true) {
				LaunchShield();
			}
			else {
				this->OnFire();
			}
			return GestEnum::LEFTHAND;
		}
		return (GestEnum::NONE);
	}
	return (GestEnum::NONE);
}

void AMagUsPlayerCharacter::Timer_DoubleTapReset() {
	DoubleTap = EDoubleTap::DT_Reset;
}

void AMagUsPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	WorldTimerManager.SetTimer(this, &AMagUsPlayerCharacter::RegenPlayer, RealAttr->GetDefaultObject<UAttributes>()->RegenerationRate, true);

	// Change Speed of character
	UCharacterMovementComponent*  CharacterMovement = GetCharacterMovement();
	GetCharacterMovement()->MaxWalkSpeed = RealAttr->GetDefaultObject<UAttributes>()->Speed;
	Cast<AMagUsPlayerController>(GetController())->SetInteractiveDistance(LockMaxDistance);
}

void AMagUsPlayerCharacter::RegenPlayer()
{
	float diffHealth = RealAttr->GetDefaultObject<UAttributes>()->MaxHealth - Health;

	Health += MIN(diffHealth, RealAttr->GetDefaultObject<UAttributes>()->Regeneration);
}
