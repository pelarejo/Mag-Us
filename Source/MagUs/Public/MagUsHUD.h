// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "MagUsHUD.generated.h"

UCLASS()
class AMagUsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMagUsHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	void ResetDefaultCrosshairPosition();
	void SetCrosshairPosition(const FVector& Position);

	void mytest(FVector& position);

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	bool bUseLockedActorPosition;
	FVector LockedActorPosition;
};

