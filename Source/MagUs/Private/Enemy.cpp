// Fill out your copyright notice in the Description page of Project Settings.

#include "MagUs.h"
#include "Enemy.h"

AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	Mesh->SetSkeletalMesh(ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P")->SkeletalMesh));
}




