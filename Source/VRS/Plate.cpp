// Fill out your copyright notice in the Description page of Project Settings.


#include "Plate.h"


// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	// UStaticMesh *qwe = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	// StaticMeshComponent->SetStaticMesh(qwe);

	cube = CreateDefaultSubobject<UStaticMeshComponent>("cube");
	RootComponent = cube;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	UStaticMesh* Asset = MeshAsset.Object;

    cube->SetStaticMesh(Asset);
}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
