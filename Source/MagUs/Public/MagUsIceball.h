#pragma once
#include "MagUsProjectile.h"
#include "MagUsIceball.generated.h"

UCLASS(config = Game)
class AMagUsIceball : public AMagUsProjectile
{
	GENERATED_BODY()

public:
	AMagUsIceball(const FObjectInitializer& ObjectInitializer);
	~AMagUsIceball();
};

