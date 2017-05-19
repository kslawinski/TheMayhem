// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Target.h"
#include "MovingTarget.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API AMovingTarget : public ATarget
{
	GENERATED_BODY()

private:
	FVector currentVelocity;
	FVector direction;
	float speed;
	float movementDistance;


	bool movingRight = true;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float frictionFactor;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Setup")
	float maxMovementDistance = 100.0f;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Setup")
	float minMovementDistance = -50.0f;
	
};
