// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Bullet.h"

ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh Component"), false);
	bulletMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentDeltaTime = DeltaTime;

	currentVelocity = direction * speed;

	// Apply friction
	float scale = 1.0f - (DeltaTime * 0.2f);
	speed *= scale;

	FVector NewLocation = GetActorLocation();


	//FRotator CurrentRotation = GetActorRotation();
	//FRotator NewRotation = FRotator(0.0f, 1.0f, 0.0f);

	if (!currentVelocity.IsZero())
	{
		NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


		SetActorLocation(NewLocation);
	}
//	SetActorRotation(CurrentRotation + NewRotation * rotationSpeed * DeltaTime);
}

void ABullet::BulletFireSetup(FVector direction, float speed)
{
	this->direction = direction;
	this->speed = speed;
}
