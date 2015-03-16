// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsVrCrosshair.h"




AMagUsVrCrosshair::AMagUsVrCrosshair(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer) {
	USceneComponent* SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootScene"));
	RootComponent = SceneComponent;

	CrosshairTex = NULL;

	CrosshairSprite = ObjectInitializer.CreateDefaultSubobject<UBillboardComponent>(this, TEXT("CrosshairPic"));
	CrosshairSprite->SetHiddenInGame(false);
	CrosshairSprite->AttachParent = SceneComponent;
	CrosshairSprite->SetRelativeScale3D(FVector(5.0f, 5.0f, 0.0f));
}

void AMagUsVrCrosshair::SetPosition(const FVector& Position) {
	if (CrosshairTex != NULL && Position.IsZero() == false)
		RootComponent->SetWorldLocation(Position);
}

void AMagUsVrCrosshair::SetScale(const FVector& Scale) {
	if (CrosshairTex != NULL && Scale.IsZero() == false)
		CrosshairSprite->SetRelativeScale3D(Scale);
}

void AMagUsVrCrosshair::SetTexture(class UTexture2D* CrosshairTex_) {
	CrosshairTex = CrosshairTex_;
	CrosshairSprite->SetSprite(CrosshairTex);
}

void AMagUsVrCrosshair::HideCross() {
	CrosshairSprite->SetHiddenInGame(true);
}

void AMagUsVrCrosshair::ShowCross() {
	CrosshairSprite->SetHiddenInGame(false);
}