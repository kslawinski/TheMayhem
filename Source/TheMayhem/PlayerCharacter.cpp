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
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	currentDeltaTime = DeltaTime;

	currentVelocity = FVector(0.0, 0.0, 0.0);
	if (!speed == 0)
	{
		
		currentVelocity = GetActorForwardVector();
		currentVelocity *= speed;

	}
		


		if (!sideSpeed == 0)
		{
			currentVelocity = GetActorRightVector();
			currentVelocity *= sideSpeed;
		}



	// Apply friction
	float scale = 1.0f - (DeltaTime * 0.8f);
	speed *= scale;

	FVector NewLocation = GetActorLocation();

	if (!currentVelocity.IsZero())
	{
			NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


			SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::MoveForward(float value)
{
	// Accelerate and decelerate the player
	speed += FMath::Clamp(value, -1.0f, 1.0f) * 100.0f * currentDeltaTime;
	speed = FMath::Clamp(speed, -100.0f, 200.0f);



	UE_LOG(LogTemp, Warning, TEXT("velocity is : %s speed is : %f"), *currentVelocity.ToString(),speed);
}

void APlayerCharacter::MoveRight(float value)
{
	sideSpeed += FMath::Clamp(value, -1.0f, 1.0f) * 100.0f * currentDeltaTime;
	sideSpeed = FMath::Clamp(sideSpeed, -70.0f, 70.0f);


}

