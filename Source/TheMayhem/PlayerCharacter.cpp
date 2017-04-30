// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "PlayerCharacter.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	characterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Mesh"));
	characterMesh->SetupAttachment(RootComponent);
	characterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
	characterCamera->SetupAttachment(characterMesh); 

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (TObjectIterator<APickup> act; act; ++act)
	{
			APickup* pickup = *act;
			pickups.Add(*act);
			UE_LOG(LogTemp, Warning, TEXT("Found %s"), *pickup->GetName())
	}

	if (true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Found %s"), *pickup->GetName())
	}

	//speed = 100.0f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Direction is: %s"), *direction.ToString());

	currentDeltaTime = DeltaTime;

	currentVelocity = direction * speed;

	// Apply friction
	float scale = 1.0f - (DeltaTime * 0.9f);
	speed *= scale;

	FVector NewLocation = GetActorLocation();
	
	
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotator(0.0f, 1.0f, 0.0f);

	if (!currentVelocity.IsZero())
	{
			NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


			SetActorLocation(NewLocation);
	}
	SetActorRotation(CurrentRotation + NewRotation * rotationSpeed * DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateRight", this, &APlayerCharacter::RotateRight);
}

void APlayerCharacter::MoveForward(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorForwardVector() * value;
		speed = 100.0f;
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorRightVector() * value;
		speed = 100.0f;
	}
}

void APlayerCharacter::RotateRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		rotationSpeed = value * 100.0f;
	}
	else
	{
		rotationSpeed = 0;
	}
}

AActor* APlayerCharacter::FindClosestActor(TArray<AActor*> actors)
{
	AActor* closestActor = nullptr;
	float closestDistanceSqr = (float)1e10;	// Very big number!

	for (int32 i = 0; i < actors.Num(); i++)
	{
		FVector distanceToTarget = (closestActor[i].GetActorLocation() - this->GetActorLocation());

		if (distanceToTarget.SizeSquared() < closestDistanceSqr)
		{
			closestDistanceSqr = distanceToTarget.SizeSquared();
			closestActor = &closestActor[i];
		}
	}

	return closestActor;
}
