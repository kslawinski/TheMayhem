// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "AmmoPickup.h"

/////////////////////////////CUSTOM CODE//////////////////////////////////
AAmmoPickup::AAmmoPickup()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/ammo.ammo'")); // load a mesh from a file
	pickupMesh->SetStaticMesh(MeshObj.Object);

	pickupMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	pickupMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
}

/////////////////////////////////////////////////////////////////////////////
