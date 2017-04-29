// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh Component"), false);
	pickupMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	//this->Tags.Add(FName("Pickup"));
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = FRotator(0.0f, 1.0f, 0.0f);
	pickupMesh->SetRelativeRotation(pickupMesh->RelativeRotation + rotation * rotationSpeed * DeltaTime);
}

