// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsCharacter.h"
#include "MagUsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Engine.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////////
// AMagUsCharacter

AMagUsCharacter::AMagUsCharacter(const FObjectInitializer& ObjectInitializer)
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
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Default Lock Distance (Random values, they are set in BP)
	LockMaxDistance = 15000;
	LockMinDistance = 1000;

	LockedActor = NULL;
	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Change Speed of character
	UCharacterMovementComponent*  CharacterMovement = GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = Speed;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMagUsCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMagUsCharacter::OnFire);
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMagUsCharacter::TouchStarted);

	InputComponent->BindAction("Lock", IE_Pressed, this, &AMagUsCharacter::OnLock);
	InputComponent->BindAction("Lock", IE_Released, this, &AMagUsCharacter::OffLock);

	InputComponent->BindAxis("MoveForward", this, &AMagUsCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMagUsCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMagUsCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMagUsCharacter::LookUpAtRate);
}

void AMagUsCharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OUCH, took " + FString::SanitizeFloat(DamageTaken) + " damages from " + PawnInstigator->GetName() + " with " + DamageCauser->GetName()));
	}
}

void AMagUsCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		FRotator SpawnRotation = GetControlRotation();

		// SpawnOffset is in camera space, so transform it to world space before offsetting from the character location to find the final spawn position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// Set the instigator of the projectile
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// spawn the projectile
			AMagUsProjectile* Projectile = World->SpawnActor<AMagUsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			Projectile->SetDamage(this->Strength);
		}
	}

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

void AMagUsCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

void AMagUsCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMagUsCharacter::MoveRight(float Value)
{
	if (Value != 0.0f) {
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMagUsCharacter::AddControllerYawInput(float Val) {
	//Disable manual rotation when in locked mode
	if (LockedActor == NULL) {
		Super::AddControllerYawInput(Val);
	}
}

void AMagUsCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMagUsCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMagUsCharacter::OnLock() {
	FHitResult OutHit = FHitResult(ForceInit);
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * LockMaxDistance);
	FCollisionObjectQueryParams Pawns(ECC_Pawn);

	FCollisionQueryParams TraceParams(FName(TEXT("Lock_Trace")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	APlayerController* PC = Cast<APlayerController>(GetController());
	check(PC);
	if (GetWorld()->LineTraceSingle(OutHit, Start, End, TraceParams, Pawns) == true
		&& PC->LineOfSightTo(OutHit.GetActor()) == true) {
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, "Locking " + OutHit.GetActor()->GetName());
		LockedActor = OutHit.GetActor();
	}
}

void AMagUsCharacter::OffLock() {
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

void AMagUsCharacter::InLock_Tick(float DeltaSeconds) {
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

void AMagUsCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (LockedActor != NULL) {
		InLock_Tick(DeltaSeconds);
	}
}

// Detect if out of camera view using angle && render time (* 2 for float margin of error)
bool AMagUsCharacter::IsLockedActorInFrustum(const float FOVAngle, const float DeltaSeconds) {
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

bool AMagUsCharacter::IsLockedActorWithinDistance() {
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

void AMagUsCharacter::Killed(AActor* Someone) {
	if (Someone == LockedActor) {
		OffLock();
	}
}