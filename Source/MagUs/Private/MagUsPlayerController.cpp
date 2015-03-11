// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsPlayerController.h"
#include "Engine.h"

const float AMagUsPlayerController::CurrentSP = 90.0f;

AMagUsPlayerController::AMagUsPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InteractionDistance = 2500; // some random value
}

void AMagUsPlayerController::BeginPlay() {
	Super::BeginPlay();
	HMDWorldLocation = PlayerCameraManager->GetCameraLocation();
	ConsoleCommand(FString("hmd sp " + FString::SanitizeFloat(CurrentSP)), true); // Should be activated when oculus entered
}

void AMagUsPlayerController::Tick(float DeltaSeconds) {
	HMDWorldLocation = PlayerCameraManager->GetCameraLocation();
}

void AMagUsPlayerController::SetInteractiveDistance(int32 Distance) {
	InteractionDistance = Distance;
}

FInteractive AMagUsPlayerController::TraceFromCamera(const ECollisionChannel Collision) {
	return TraceFromCamera(ECC_TO_BITFIELD(Collision));
}

FInteractive AMagUsPlayerController::TraceFromCamera(const uint32 Collisions) {
	OutHit = FHitResult(ForceInit);
	const FVector Start = HMDWorldLocation;
	const FVector End = Start + (PlayerCameraManager->GetActorForwardVector() * InteractionDistance);
	FCollisionObjectQueryParams CollisionChannels(Collisions);

	FCollisionQueryParams TraceParams(FName(TEXT("Interactive_Trace")), true, GetCharacter());
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	FInteractive Result = { NULL, NULL, false };
	if (GetWorld()->LineTraceSingle(OutHit, Start, End, TraceParams, CollisionChannels) == true) {
		if (LineOfSightTo(OutHit.GetActor()) == true) {
			Result.Actor = OutHit.GetActor();
		}
		Result.Component = OutHit.GetComponent();
		if (Result.Component != NULL && Result.Component->ComponentHasTag(FName(TEXT("Interactive"))) == true) {
			Result.bHitInteractive = true;
		}
	}
	return Result;
}

FVector AMagUsPlayerController::FindCrosshairPosition() {
	TraceFromCamera(ECC_TO_BITFIELD(ECC_WorldStatic)
				| ECC_TO_BITFIELD(ECC_Pawn)
				| ECC_TO_BITFIELD(ECC_PhysicsBody));
//	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, OutHit.Location.ToString());
	return OutHit.Location;
}