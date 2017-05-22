// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "CustomObject.h"


// Sets default values
ACustomObject::ACustomObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh collision volume"), false);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	collisionMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> CustomObjectMeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialObj(TEXT("MaterialInstanceConstant'/Game/Materials/collisionBoxMat.collisionBoxMat'"));  // load material from file

	collisionMesh->SetStaticMesh(CustomObjectMeshObj.Object);
	collisionMesh->SetMaterial(0, MaterialObj.Object); // set material to mesh

	collisionMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	collisionMesh->CastShadow = false;
	


	//UE_LOG(LogTemp, Warning, TEXT("radius is: %s"), *boxSize.ToString())
	
	//SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ACustomObject::BeginPlay()
{
	Super::BeginPlay();
	UpdateCollisionBounds();
}

// Called every frame
void ACustomObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomObject::UpdateCollisionBounds()
{
	//UE_LOG(LogTemp, Warning, TEXT("collision bounds updated"))
	FVector origin, bounds;

	GetActorBounds(false,origin, bounds);

	collisionXMin = origin.X - bounds.X;
	collisionXMax = origin.X + bounds.X;
	collisionYMin = origin.Y - bounds.Y;
	collisionYMax = origin.Y + bounds.Y;
	collisionZMin = origin.Z - bounds.Z;
	collisionZMax = origin.Z + bounds.Z;

}

bool ACustomObject::CheckCollision(FVector testVector, float radius, float height)
{

	/////////////////////////////CUSTOM CODE modified collision check fucntion//////////////////////////////////

	bool isColliding = false;

	bool collidingX = false;
	bool collidingY = false;
	bool collidingZ = false;


	if (((testVector.X + radius) >= collisionXMin) && ((testVector.X - radius) <= collisionXMax))
	{
		collidingX = true;
	}

	if (((testVector.Y + radius) >= collisionYMin) && ((testVector.Y - radius) <= collisionYMax))
	{
		collidingY = true;
	}

	if ((testVector.Z) >= collisionZMin && ((testVector.Z - height) <= collisionZMax + height))
	{
		collidingZ = true;
	}

	if (collidingX && collidingY && collidingZ)
	{
		isColliding = true;
	}

	return isColliding;
}

