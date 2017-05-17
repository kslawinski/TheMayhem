// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Rocket.h"

ARocket::ARocket()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("//StaticMesh'/Game/Geometry/BazookaAmmo.BazookaAmmo'")); // load a mesh from a file
	bulletMesh->SetStaticMesh(MeshObj.Object);

	collisionMesh->SetWorldScale3D(FVector(0.4f, 0.1f, 0.1f));
	bulletMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	bulletMesh->SetRelativeRotation(FRotator(0.0f,-90,0.0f));
	frictionFactor = 0.05f;
}
