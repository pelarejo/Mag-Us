// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

AMagUsHUD::AMagUsHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	bUseLockedActorPosition = false;
}

#include "Engine.h"

void AMagUsHUD::DrawHUD()
{
	Super::DrawHUD();

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	if (bUseLockedActorPosition == true) {
		FVector Projection = Canvas->Project(LockedActorPosition);
		CrosshairDrawPosition.X = Projection.X;
		CrosshairDrawPosition.Y = Projection.Y;
	}
	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AMagUsHUD::ResetDefaultCrosshairPosition() {
	bUseLockedActorPosition = false;
}

/**
**
*/
void AMagUsHUD::SetCrosshairPosition(const FVector& Position) {
	LockedActorPosition.X = Position.X;
	LockedActorPosition.Y = Position.Y;
	LockedActorPosition.Z = Position.Z;
	bUseLockedActorPosition = true;
}