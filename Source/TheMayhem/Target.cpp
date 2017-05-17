// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Target.h"

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	targetHealth = 100.0f;
}

ATarget::ATarget()
{
	targetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"), false);
	targetMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	targetMesh->SetStaticMesh(MeshObj.Object);

	targetMesh->SetWorldScale3D(FVector(0.1f, 0.5f, 0.5f));
	collisionMesh->SetWorldScale3D(FVector(0.2f, 0.6f, 0.6f));
}

void ATarget::GiveDamage(float damage)
{

}

