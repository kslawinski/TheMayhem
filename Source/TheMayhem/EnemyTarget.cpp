// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "EnemyTarget.h"

AEnemyTarget::AEnemyTarget()
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(RootComponent);
	weaponMesh->SetRelativeLocation(FVector(70.0f, 45.0f, 30.0f));
	weaponMesh->SetRelativeRotation(FRotator(0.0f, -90.0f,0.0f));
	weaponMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GunMeshObj(TEXT("StaticMesh'/Game/Geometry/gun.gun'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BazookaMeshObj(TEXT("StaticMesh'/Game/Geometry/bazooka.bazooka'")); // load a mesh from a file
	gunMesh = GunMeshObj.Object;
	bazookaMesh = BazookaMeshObj.Object;

	gunMoozle = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Moozle point"));
	gunMoozle->SetupAttachment(weaponMesh);

	weaponMesh->SetStaticMesh(gunMesh); // for now

	targetMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.6f));
	collisionMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
}

void AEnemyTarget::Shoot()
{

}

