// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsAICharacter.h"
#include "MagUsProjectile.h"
#include "MagUsPlayerCharacter.h"
#include "Engine.h"

AMagUsAICharacter::AMagUsAICharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Default offset from the character location for projectiles to spawn
	ProjectileOffset = FVector(40.0f, 0.0f, 0.0f);
}

void AMagUsAICharacter::OnFire()
{
	// Get the right Spell to cast
	TSubclassOf<class AMagUsProjectile> Spell = ProjectileArray[(int)this->spellType];

	// try and fire a projectile
	if (Spell)
	{
		FRotator SpawnRotation = GetControlRotation();

		// SpawnOffset is in camera space, so transform it to world space before offsetting from the character location to find the final spawn position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// Set the instigator of the projectile
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// spawn the projectile
			AMagUsProjectile* Projectile = World->SpawnActor<AMagUsProjectile>(Spell, SpawnLocation, SpawnRotation, SpawnParams);
			Projectile->SetDamage(RealAttr->GetDefaultObject<UAttributes>()->Strength); // For now, will be replaced by damage calc in Projectile
		}
	}
	/*
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
	}*/
}

void AMagUsAICharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	this->Health -= DamageTaken;

	if (this->Health < 0)
	{
		/** Check if the Instigator is the player then signal an AI is killed */
		AMagUsPlayerCharacter *Player(Cast<AMagUsPlayerCharacter>(PawnInstigator));
		if (Player)
			Player->Killed(this);

		Destroy();
	}
}

void AMagUsAICharacter::BeginPlay()
{
	// Change Speed of character
	UCharacterMovementComponent*  CharacterMovement = GetCharacterMovement();
	GetCharacterMovement()->MaxWalkSpeed = RealAttr->GetDefaultObject<UAttributes>()->Speed;
}

void AMagUsAICharacter::setSpellType(int32 newValue)
{
	this->spellType = (GestEnum)newValue;
}