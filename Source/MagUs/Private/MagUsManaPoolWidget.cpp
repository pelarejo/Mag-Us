// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsManaPoolWidget.h"

AMagUsManaPoolWidget::AMagUsManaPoolWidget(const FObjectInitializer& ObjInit)
: Super(ObjInit) {
	USceneComponent* SceneComponent = ObjInit.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootScene"));
	RootComponent = SceneComponent;

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgBP(TEXT("/Game/Blueprints/UI/ManaPoolWidget_BP"));
	WidgetTemplate = WidgBP.Class;

	static ConstructorHelpers::FClassFinder<AActor> WidgActorBP(TEXT("/Game/Blueprints/UI/ManaPoolWidgetActor_BP"));
	Widget3DTemplate = WidgActorBP.Class;
}

void AMagUsManaPoolWidget::CreateUserWidget(AMagUsPlayerController* PC) {
	WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);
	WidgetInstance->AddToViewport();
	WidgetInstance->SetRenderScale(FVector2D(1.0f, 0.3f));
	HideWidget();

	Widget3DActor = GetWorld()->SpawnActor<AActor>(Widget3DTemplate);
	Widget3DActor->SetActorHiddenInGame(true);
}

void AMagUsManaPoolWidget::ShowWidget() {
//	WidgetInstance->SetVisibility(ESlateVisibility::Visible);
}

void AMagUsManaPoolWidget::HideWidget() {
	WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
}

void AMagUsManaPoolWidget::Set3DWidgetLocation(const FVector& Location) {
	Widget3DActor->SetActorLocation(Location);
}

void AMagUsManaPoolWidget::Set3DWidgetRotation(const FVector& Rotation) {
	FMatrix Mat = FRotationMatrix::MakeFromZ(Rotation);
	Widget3DActor->SetActorRotation(Mat.Rotator());
}

void AMagUsManaPoolWidget::BeginPlay() {
	Super::BeginPlay();
	
}