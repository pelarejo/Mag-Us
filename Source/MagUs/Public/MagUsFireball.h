#pragma once
#include "MagUsProjectile.h"
#include "MagUsFireball.generated.h"

UCLASS(config = Game)
class AMagUsFireball : public AMagUsProjectile
{
	GENERATED_BODY()

public:
	AMagUsFireball(const FObjectInitializer& ObjectInitializer);
//	AMagUsFireball();
	~AMagUsFireball();
};

