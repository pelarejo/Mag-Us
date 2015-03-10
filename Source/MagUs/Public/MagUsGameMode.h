// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "Environnement.h"
#include "MagUsGameMode.generated.h"

UCLASS(minimalapi)
class AMagUsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMagUsGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, Category = SpellManagement)
	AEnvironnement* getManaPool();

private:
	UPROPERTY()
	TSubclassOf<AEnvironnement> EnvironnementClass;

	UPROPERTY()
	AEnvironnement* ManaPool;
};



