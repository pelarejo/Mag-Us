// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MagUsPlayerController.generated.h"

/**
 * 
 */

struct FInteractive {
	bool bHitInteractive;
	AActor* Actor;
	UPrimitiveComponent* Component;
};

UCLASS()
class MAGUS_API AMagUsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMagUsPlayerController(const FObjectInitializer& ObjectInitializer);

	void SetInteractiveDistance(int32 Distance);
	FInteractive TraceFromCamera(const ECollisionChannel Collision);
	FInteractive TraceFromCamera(const uint32 Collisions);

	FVector FindCrosshairPosition();

protected:
	void BeginPlay();
	void Tick(float DeltaSeconds) override;

private:
	static const float CurrentSP;
	FVector HMDWorldLocation;
	int32 InteractionDistance;
	FHitResult OutHit;
};
