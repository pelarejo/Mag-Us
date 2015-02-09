// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsAICharacter.h"
#include "MagUsCharacter.h"
#include "Engine.h"

void AMagUsAICharacter::ApplyDamageMomentum(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OUCH, took " + FString::SanitizeFloat(DamageTaken) + " damages from " + PawnInstigator->GetName() + " with " + DamageCauser->GetName()));
	}
	this->Health -= DamageTaken;

	if (this->Health < 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("" + this->GetName() + " died"));
		}

		/** Check if the Instigator is the player then signal an AI is killed */
		AMagUsCharacter *Player(Cast<AMagUsCharacter>(PawnInstigator));
		if (Player)
			Player->Killed(this);

		Destroy();
	}
}