// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SlateBasics.h"
#include "MagUsPlayerController.h"
#include "MagUsManaPoolWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGUS_API AMagUsManaPoolWidget : public AActor
{
	GENERATED_BODY()
	
public:
	AMagUsManaPoolWidget(const FObjectInitializer& ObjInit);

	void CreateUserWidget(AMagUsPlayerController* PC);
	void ShowWidget();
	void HideWidget();

	void Set3DWidgetLocation(const FVector& Location);
	void Set3DWidgetRotation(const FVector& Rotation);

protected:
	void BeginPlay() override;

private:
	TSubclassOf<UUserWidget> WidgetTemplate;
	UUserWidget* WidgetInstance;
	
	// Using a BP here because I can't seem to find a way
	// to set WidgetClass in UWidgetComponent in c++
	TSubclassOf<AActor> Widget3DTemplate;
	AActor* Widget3DActor;

};
