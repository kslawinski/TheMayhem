// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "HealthPickup.h"

AHealthPickup::AHealthPickup()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/1st_aid_kit.1st_aid_kit'")); // load a mesh from a file
	pickupMesh->SetStaticMesh(MeshObj.Object);

	pickupMesh->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	pickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
}


