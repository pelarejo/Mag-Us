// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MagUsBuff.h"
#include "MagUsBuffDef.generated.h"

/**
 * Base des buffs défensifs, à renommer en AMagUsShield ?
 */
UCLASS()
class MAGUS_API AMagUsBuffDef : public AMagUsBuff
{
	GENERATED_BODY()

public:
	AMagUsBuffDef(const FObjectInitializer& ObjectInitializer);
	//AMagUsBuffDef();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkelMeshComponents)
	//AStaticMeshActor * BuffMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkelMeshComponents)
	//TSubclassOf<class UStaticMesh> BuffMesh;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkelMeshComponents)
	//UStaticMesh* BuffMesh;
	//class UStaticMeshComponent* GetStaticMeshComponent() const;

	
	
};
