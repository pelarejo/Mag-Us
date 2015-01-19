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

	bUseDefaultCrosshairPosition = true;
}

/*
** I had to use a boolean value because I couldn't use Canvas in constructor making saving
** a default centered position for the crosshair impossible.
*/
void AMagUsHUD::DrawHUD()
{
	Super::DrawHUD();

	if (bUseDefaultCrosshairPosition == true) {
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		CrosshairDrawPosition = FVector2D((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
											(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));
	}

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void AMagUsHUD::ResetDefaultCrosshairPosition() {
	bUseDefaultCrosshairPosition = true;
}

void AMagUsHUD::SetCrosshairPosition(FVector2D position) {
	bUseDefaultCrosshairPosition = false;
	CrosshairDrawPosition = position;
}