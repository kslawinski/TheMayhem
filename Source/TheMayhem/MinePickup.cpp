// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "MinePickup.h"

AMinePickup::AMinePickup()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/mine.mine'")); // load a mesh from a file
	pickupMesh->SetStaticMesh(MeshObj.Object);

	pickupMesh->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	pickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));

	quantity = 40.f;
	rotationSpeed = 50.0f;
}


