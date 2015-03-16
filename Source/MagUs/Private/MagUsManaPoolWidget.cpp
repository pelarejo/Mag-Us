// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "MagUsManaPoolWidget.h"

AMagUsManaPoolWidget::AMagUsManaPoolWidget(const FObjectInitializer& ObjInit)
: Super(ObjInit) {
	USceneComponent* SceneComponent = ObjInit.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootScene"));
	RootComponent = SceneComponent;

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgBP(TEXT("/Game/Blueprints/UI/ManaPoolWidget_BP2"));
	WidgetTemplate = WidgBP.Class;

	static ConstructorHelpers::FClassFinder<AActor> WidgActorBP(TEXT("/Game/Blueprints/UI/ManaPoolWidgetActor_BP"));
	Widget3DTemplate = WidgActorBP.Class;
}

void AMagUsManaPoolWidget::CreateUserWidget(AMagUsPlayerController* PC) {
	WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetTemplate);
	WidgetInstance->AddToViewport();
	HideWidget();

	Widget3DActor = GetWorld()->SpawnActor<AActor>(Widget3DTemplate);
	Widget3DActor->SetActorScale3D(FVector(0.02f, 0.01f, 0.05f));
	Widget3DActor->AttachRootComponentTo(PC->GetCharacter()->GetMesh(), "hand_rSocket");
	Widget3DActor->SetActorRelativeRotation(FRotator(0, 0, 180));
}

void AMagUsManaPoolWidget::ShowWidget() {
	WidgetInstance->SetVisibility(ESlateVisibility::Visible);
}

void AMagUsManaPoolWidget::HideWidget() {
	WidgetInstance->SetVisibility(ESlateVisibility::Hidden);
}

//Not used since attached to socket
void AMagUsManaPoolWidget::Set3DWidgetLocation(const FVector& Location) {
	//FVector Loc = Location - 2 * Widget3DActor->GetActorForwardVector();
	//Widget3DActor->SetActorLocation(Loc);
}

//Not used since attached to socket
void AMagUsManaPoolWidget::Set3DWidgetRotation(const FVector& Rotation) {
	//FMatrix Mat = FRotationMatrix::MakeFromZ(Rotation);
	//Widget3DActor->SetActorRotation(Mat.Rotator());
}

void AMagUsManaPoolWidget::BeginPlay() {
	Super::BeginPlay();
	
}