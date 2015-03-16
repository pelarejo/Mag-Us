// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsHUD.h"
#include "MagUsPlayerController.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Engine.h"
#include "HeadMountedDisplay.h"

AMagUsHUD::AMagUsHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/Textures/Crosshair"));
	CrosshairTex = CrosshairTexObj.Object;

	bUseLockedActorPosition = false;
	bDraw3DHUD = false;
}

void AMagUsHUD::DrawHUD()
{
	Super::DrawHUD();
	if (bDraw3DHUD == true){
		DrawVrCrosshairPosition();
	}
	else {
		DrawCrosshairPosition();
	}
}

void AMagUsHUD::ResetDefaultCrosshairPosition() {
	bUseLockedActorPosition = false;
}

void AMagUsHUD::SetCrosshairPosition(const FVector& Position) {
	LockedActorPosition.X = Position.X;
	LockedActorPosition.Y = Position.Y;
	LockedActorPosition.Z = Position.Z;
	bUseLockedActorPosition = true;
}

void AMagUsHUD::SetVrManaPoolPositionRotation(const FVector& Position, const FVector& Rotation) {
	ManaWidget->Set3DWidgetLocation(Position);
	ManaWidget->Set3DWidgetRotation(Rotation);
}

void AMagUsHUD::BeginPlay() {
	Super::BeginPlay();
	VrCrosshair = GetWorld()->SpawnActor<AMagUsVrCrosshair>();
	VrCrosshair->SetTexture(CrosshairTex);
	
	ManaWidget = GetWorld()->SpawnActor<AMagUsManaPoolWidget>();
	AMagUsPlayerController* PC = CastChecked<AMagUsPlayerController>(GetOwningPlayerController());
	ManaWidget->CreateUserWidget(PC);
	ManaWidget->ShowWidget();
}

void AMagUsHUD::Tick(float DeltaSeconds) {
	if (GEngine != NULL && GEngine->IsStereoscopic3D() != bDraw3DHUD) {
		bDraw3DHUD = GEngine->IsStereoscopic3D();
		(bDraw3DHUD == true) ? ManaWidget->HideWidget() : ManaWidget->ShowWidget();
		(bDraw3DHUD == true) ? VrCrosshair->ShowCross() : VrCrosshair->HideCross();
	}
}

void AMagUsHUD::DrawCrosshairPosition() {
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

void AMagUsHUD::DrawVrCrosshairPosition() {
	AMagUsPlayerController* PC = CastChecked<AMagUsPlayerController>(GetOwningPlayerController());
	FVector ActorLocation = PC->PlayerCameraManager->GetCameraLocation();
	FVector Position;

	if (bUseLockedActorPosition == true) {
		Position = LockedActorPosition;
	}
	else {
		Position = PC->FindCrosshairPosition();
	}
	Position = Position + 0.2f * (ActorLocation - Position); // So that there is no clipping
	VrCrosshair->SetPosition(Position);
}