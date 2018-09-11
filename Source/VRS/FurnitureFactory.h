// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FurnitureFactory.generated.h"

UCLASS()
class VRS_API AFurnitureFactory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFurnitureFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "App")
	void init(int id);

	FHttpModule* http;
	void onResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool successful);
	void onMeshGet(FHttpRequestPtr request, FHttpResponsePtr response, bool successful, TSharedPtr<FJsonObject> json);
};
