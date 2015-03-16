// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine.h"
#include "MagUsPlayerController.h"
#include "MagUsVrCrosshair.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsVrCrosshair : public AActor
{
	GENERATED_BODY()

public:
		AMagUsVrCrosshair(const FObjectInitializer& ObjectInitializer);
		void SetPosition(const FVector& Position);
		void SetScale(const FVector& Scale);
		void SetTexture(class UTexture2D* CrosshairTex);
		void HideCross();
		void ShowCross();

private:
	class UTexture2D* CrosshairTex;
	UBillboardComponent* CrosshairSprite;
	
};
