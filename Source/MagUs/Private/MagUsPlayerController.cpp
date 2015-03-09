// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsPlayerController.h"
#include "Engine.h"

AMagUsPlayerController::AMagUsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionDistance = 2500; // some random value
}

void AMagUsPlayerController::BeginPlay() {
	Super::BeginPlay();
	HMDWorldLocation = PlayerCameraManager->GetCameraLocation();
}

void AMagUsPlayerController::Tick(float DeltaSeconds) {
	HMDWorldLocation = PlayerCameraManager->GetCameraLocation();
}

void AMagUsPlayerController::SetInteractiveDistance(int32 Distance) {
	InteractionDistance = Distance;
}

FInteractive AMagUsPlayerController::GetInteractive() {
	FHitResult OutHit = FHitResult(ForceInit);
	const FVector Start = HMDWorldLocation;
	const FVector End = Start + (PlayerCameraManager->GetActorForwardVector() * InteractionDistance);
	FCollisionObjectQueryParams CollisionChannel(ECC_Pawn);

	FCollisionQueryParams TraceParams(FName(TEXT("Interactive_Trace")), true, GetCharacter());
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	FInteractive Result = {NULL, NULL, false};
	if (GetWorld()->LineTraceSingle(OutHit, Start, End, TraceParams, CollisionChannel) == true) {
		if (LineOfSightTo(OutHit.GetActor()) == true) {
			Result.Actor = OutHit.GetActor();
		}
		Result.Component = OutHit.GetComponent();
		if (Result.Component->ComponentHasTag(FName(TEXT("Interactive"))) == true) {
			Result.bHitInteractive = true;
		}
	}
	return Result;
}