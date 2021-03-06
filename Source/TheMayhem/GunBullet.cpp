// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "GunBullet.h"

AGunBullet::AGunBullet()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/Bullet.bullet'")); // load a mesh from a file
	bulletMesh->SetStaticMesh(MeshObj.Object);

	collisionMesh->SetWorldScale3D(FVector(0.03f, 0.03f, 0.03f));
	bulletMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
}
