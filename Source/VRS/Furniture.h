// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralEntity.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Furniture.generated.h"

UCLASS()
class VRS_API AFurniture : public AProceduralEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFurniture();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
