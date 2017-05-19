// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "MovingTarget.h"


// Called every frame
void AMovingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (movementDistance >= maxMovementDistance)
	{
		movingRight = false;
	}
	else if(movementDistance <= minMovementDistance)
	{
		movingRight = true;
	}

	if (movingRight)
	{
		movementDistance += DeltaTime * speed;
		direction = GetActorRightVector();
	}
	else
	{
		movementDistance -= DeltaTime * speed;
		direction = -GetActorRightVector();
	}



	speed = 20.0f;

	currentVelocity = direction * speed;

	// Apply friction
	float scale = 1.0f - (DeltaTime * frictionFactor);
	speed *= scale;

	FVector NewLocation = GetActorLocation();


	if (!currentVelocity.IsZero())
	{
		NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


		SetActorLocation(NewLocation);
	}
}

