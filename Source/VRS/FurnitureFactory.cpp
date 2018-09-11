// Fill out your copyright notice in the Description page of Project Settings.

#include "FurnitureFactory.h"
#include "Furniture.h"
#include "Plate.h"
#include "Components/PointLightComponent.h"

// Sets default values
AFurnitureFactory::AFurnitureFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = false;

	// const TCHAR * test = TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'");
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(test);
	// StaticMeshComponent->SetStaticMesh(MeshRef.Object);

	http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AFurnitureFactory::BeginPlay()
{
	Super::BeginPlay();
}

void AFurnitureFactory::init(int id) {
	TSharedRef<IHttpRequest> Request = http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AFurnitureFactory::onResponse);
	//This is the url on which to process the request
	FString url = "http://pravote.bytesbay.fun/vrs/data-";
	url.AppendInt(id);
	url.Append(".json");
	Request->SetURL(url);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

// Called every frame
void AFurnitureFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFurnitureFactory::onResponse(FHttpRequestPtr request, FHttpResponsePtr response, bool successful) {
	UE_LOG(LogTemp, Warning, TEXT(" -- HTTP response got! Going to parse root JSON."));

	// Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> root_json;

	// Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(response->GetContentAsString());

	// Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(reader, root_json)) {

		TArray<TSharedPtr<FJsonValue>> plates = root_json->GetArrayField("plates");
		uint32_t array_size = plates.Num();

		for (uint16_t i = 0; i < array_size; i++) {

			TSharedPtr<FJsonObject> json = plates[i]->AsObject();

			TSharedPtr<FJsonObject> pos = json->GetObjectField("position");
			FVector location(
				pos->GetIntegerField("x"),
				pos->GetIntegerField("y"),
				pos->GetIntegerField("z")
			);

			TSharedPtr<FJsonObject> rot = json->GetObjectField("rotation");
			FRotator rotate(
				rot->GetIntegerField("y"),
				rot->GetIntegerField("z"),
				rot->GetIntegerField("x")
			);

			TSharedPtr<FJsonObject> scale = json->GetObjectField("scale");
			FVector transform(
				scale->GetNumberField("x"),
				scale->GetNumberField("y"),
				scale->GetNumberField("z")
			);

			FActorSpawnParameters SpawnInfo;
			APlate * plate = GetWorld()->template SpawnActor<APlate>(APlate::StaticClass(), location, rotate, SpawnInfo);
			plate->SetActorScale3D(transform);
		}

		TArray<TSharedPtr<FJsonValue>> entities = root_json->GetArrayField("entities");
		array_size = entities.Num();

		for (uint16_t i = 0; i < array_size; i++) {

			TSharedPtr<FJsonObject> json = entities[i]->AsObject();

			// Get the value of the json object by field name
			FString mesh_url = json->GetStringField("mesh_url");

			TSharedRef<IHttpRequest> Request = http->CreateRequest();
			Request->OnProcessRequestComplete().BindUObject(this, &AFurnitureFactory::onMeshGet, json);
			// This is the url on which to process the request
			Request->SetURL(*(mesh_url));
			Request->SetVerb("GET");
			Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
			Request->SetHeader("Content-Type", TEXT("application/json"));
			Request->ProcessRequest();

		}
	}
}
void AFurnitureFactory::onMeshGet(FHttpRequestPtr request, FHttpResponsePtr response, bool successful, TSharedPtr<FJsonObject> json) {
	UE_LOG(LogTemp, Warning, TEXT(" -- GOT MESH RESPONCE, ID: %i"), json->GetIntegerField("id"));

	TSharedPtr<FJsonObject> pos = json->GetObjectField("position");
	FVector location(
		pos->GetIntegerField("x"),
		pos->GetIntegerField("y"),
		pos->GetIntegerField("z")
	);

	TSharedPtr<FJsonObject> rotation = json->GetObjectField("rotation");
	FRotator rotate(
		rotation->GetIntegerField("y"),
		rotation->GetIntegerField("z"),
		rotation->GetIntegerField("x")
	);

	FActorSpawnParameters SpawnInfo;
	AFurniture * furniture = GetWorld()->template SpawnActor<AFurniture>(AFurniture::StaticClass(), location, rotate, SpawnInfo);

	FString rel_path = FPaths::GameContentDir();
	FString path = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*rel_path) + "tmp/mesh.obj";
	FFileHelper::SaveStringToFile(*(response->GetContentAsString()), *(path));
	furniture->loadModel(TCHAR_TO_UTF8(*path));

	if(json->GetStringField("type") == "wall-lamp") {

		TSharedPtr<FJsonObject> light = json->GetObjectField("light_position");
		FVector light_position(
			light->GetIntegerField("x"),
			light->GetIntegerField("y"),
			light->GetIntegerField("z")
		);

		//CompClass can be a BP
		UPointLightComponent* light_component = NewObject<UPointLightComponent>(furniture);
		if(light_component) {
			light_component->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above
			light_component->SetWorldLocation(light_position);
			light_component->AttachTo(furniture->GetRootComponent(), "light", EAttachLocation::KeepRelativeOffset);
		}
	}
}
