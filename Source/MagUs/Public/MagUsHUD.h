// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "MagUsVrCrosshair.h"
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

protected:
	void BeginPlay() override;

	void DrawCrosshairPosition();
	void DrawVrCrosshairPosition();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	bool bUseLockedActorPosition;
	FVector LockedActorPosition;

	AMagUsVrCrosshair* VrCrosshair;
};

