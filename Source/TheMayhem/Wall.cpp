// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Wall.h"


AWall::AWall()
{
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"), false);
	wallMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	wallMesh->SetStaticMesh(MeshObj.Object);

	wallMesh->SetWorldScale3D(FVector(0.1f, 0.5f, 0.5f));
	collisionMesh->SetWorldScale3D(FVector(0.2f, 0.6f, 0.6f));
}

