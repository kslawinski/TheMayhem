// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "LightTarget.h"


ALightTarget::ALightTarget()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> LightTargetMeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Sphere.Sphere'")); // load a mesh from a file
	targetMesh->SetStaticMesh(LightTargetMeshObj.Object);
	collisionMesh->SetStaticMesh(LightTargetMeshObj.Object);
	targetMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	collisionMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));


	lightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light Component"), false);
	lightComponent->SetupAttachment(RootComponent);
	lightComponent->SetLightColor(FColor::Red,true);

	targetHealth = 10.0f;

	//destructionMesh = CreateDefaultSubobject<UDestructibleMesh>(TEXT("destruction Mesh"), false);
	
}

