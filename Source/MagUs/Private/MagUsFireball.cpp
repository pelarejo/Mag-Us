
#include "MagUs.h"
#include "MagUsFireball.h"
#include "MagUsAICharacter.h"
#include "MagUsCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"


AMagUsFireball::AMagUsFireball(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Fireball's damage
	SetDamage(20000000000.0f);
}


AMagUsFireball::~AMagUsFireball()
{
}