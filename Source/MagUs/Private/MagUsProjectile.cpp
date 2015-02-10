// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsAICharacter.h"
#include "MagUsCharacter.h"
#include "MagUsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"

AMagUsProjectile::AMagUsProjectile(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use a sphere as a simple collision representation
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMagUsProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->ProjectileGravityScale = 0;

	// Die after 3 seconds by default
	InitialLifeSpan = 1.0f;
}

void AMagUsProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor == NULL) || (OtherActor == this) || (OtherComp == NULL))
	{
		Destroy();
		return;
	}
	
	// Try to damage character
	ACharacter* Character(Cast<AMagUsAICharacter>(OtherActor));	// Is Component an AI
	if (!Character)
		Character = (Cast<AMagUsCharacter>(OtherActor));		// Or is it the player
	if (Character)
	{
		FDamageEvent damageEvent;
		Character->ApplyDamageMomentum(this->Damage, damageEvent, this->Instigator, this);
	}
	// Only add impulse if we hit a physics
	else if (OtherComp->IsSimulatingPhysics())
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

	// Destroy projectile 
	Destroy();
}

void AMagUsProjectile::SetDamage(float damageAmount)
{
	Damage = damageAmount;
}