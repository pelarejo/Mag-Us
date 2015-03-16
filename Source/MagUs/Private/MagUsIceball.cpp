
#include "MagUs.h"
#include "MagUsIceball.h"
#include "MagUsAICharacter.h"
#include "MagUsCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine.h"


AMagUsIceball::AMagUsIceball(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Type = EManaType::ICE;
}


AMagUsIceball::~AMagUsIceball()
{
}