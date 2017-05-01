// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "CustomObject.h"


// Sets default values
ACustomObject::ACustomObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh collision volume"), false);
	collisionMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialObj(TEXT("MaterialInstanceConstant'/Game/collisionBoxMat.collisionBoxMat'"));  // load material from file

	collisionMesh->SetStaticMesh(MeshObj.Object);
	collisionMesh->SetMaterial(0, MaterialObj.Object); // set material to mesh

	collisionMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	collisionMesh->CastShadow = false;
	
	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ACustomObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

