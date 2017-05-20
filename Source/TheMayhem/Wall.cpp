// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Wall.h"


AWall::AWall()
{
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"), false);
	wallMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/Wall_400x300.Wall_400x300'")); // load a mesh from a file
	wallMesh->SetStaticMesh(MeshObj.Object);
	wallMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	//wallMesh->SetWorldScale3D(FVector(0.1f, 0.5f, 0.5f));
	collisionMesh->SetWorldScale3D(FVector(0.16f, 1.6f, 1.2f));
	collisionMesh->SetRelativeLocation(FVector(0.0f, 200.0f, 150.0f));


}

