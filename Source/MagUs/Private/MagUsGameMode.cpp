// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "MagUs.h"
#include "MagUsGameMode.h"
#include "MagUsHUD.h"
#include "MagUsCharacter.h"
#include "Engine.h"
#include "MagUsPlayerController.h"

AMagUsGameMode::AMagUsGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMagUsHUD::StaticClass();

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/Blueprints/MagUsController_BP"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

	// Load ManaPool BP with the characteristics of the environnement
	static ConstructorHelpers::FClassFinder<AEnvironnement> EnvironnementClassFinder(TEXT("/Game/Blueprints/ManaPool"));
	EnvironnementClass = EnvironnementClassFinder.Class;
}

void AMagUsGameMode::StartPlay()
{
	Super::StartPlay();
	
	// Spawn the ManaPool
	ManaPool = GetWorld()->SpawnActor<AEnvironnement>(EnvironnementClass);
}

AEnvironnement* AMagUsGameMode::getManaPool()
{
	return ManaPool;
}