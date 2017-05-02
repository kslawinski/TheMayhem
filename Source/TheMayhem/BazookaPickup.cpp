// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "BazookaPickup.h"

ABazookaPickup::ABazookaPickup()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/bazooka.bazooka'")); // load a mesh from a file
	pickupMesh->SetStaticMesh(MeshObj.Object);

	pickupMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	pickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
}


