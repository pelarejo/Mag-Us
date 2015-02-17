// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsAICharacter.h"
#include "MagUsCharacter.h"
#include "Engine.h"

void AMagUsAICharacter::OnFire()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Fire"));
	/*
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
	}*/
}

void AMagUsAICharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("AI: " + FString::SanitizeFloat(DamageTaken)));
	}
	this->Health -= DamageTaken;

	if (this->Health < 0)
	{
		/** Check if the Instigator is the player then signal an AI is killed */
		AMagUsCharacter *Player(Cast<AMagUsCharacter>(PawnInstigator));
		if (Player)
			Player->Killed(this);

		Destroy();
	}
}