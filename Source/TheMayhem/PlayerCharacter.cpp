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

	for (TActorIterator<ACustomObject> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->IsPendingKill())
		{
			continue;
		}

		ACustomObject* pickup = *ActorItr;
		sceneActors.Add(pickup);
		if (pickup)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found %s"), *pickup->GetName())
		}

	}
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


	// Simple collision detection
	if (sceneActors.Num() > 0)
	{
		closestActor = FindClosestActor(sceneActors);

		if (closestActor)
		{
			bool isColliding = closestActor->CheckCollision(GetActorLocation(), 1.0f,2.0f);

			if (isColliding)
			{
				APickup* closestPickup = Cast<APickup>(closestActor);
				if (closestPickup) // if the closest customObject is a Pickup
				{
					UE_LOG(LogTemp, Warning, TEXT("character is colliding?: %i"), isColliding)
				}
			}
		}
	}

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

ACustomObject* APlayerCharacter::FindClosestActor(TArray<ACustomObject*> actors)
{
	ACustomObject* closestActor = nullptr;
	float closestDistanceSqr = (float)1e10;	// Very big number!

	for (int32 i = 0; i < actors.Num(); i++)
	{
		FVector distanceToTarget = (actors[i]->GetActorLocation() - this->GetActorLocation());

		if (distanceToTarget.SizeSquared() < closestDistanceSqr)
		{
			closestDistanceSqr = distanceToTarget.SizeSquared();
			closestActor = actors[i];
		}
	}

	return closestActor;
}
