// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "GunPickup.h"

AGunPickup::AGunPickup()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/gun.gun'")); // load a mesh from a file
	pickupMesh->SetStaticMesh(MeshObj.Object);

	pickupMesh->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	pickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
}


