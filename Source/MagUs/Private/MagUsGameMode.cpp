// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsGameMode.h"
#include "MagUsHUD.h"
#include "MagUsCharacter.h"
#include "MagUsPlayerController.h"

AMagUsGameMode::AMagUsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/LeapMotion/Blueprints/LeapBasicRiggedCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMagUsHUD::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/Blueprints/MagUsController_BP"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}
