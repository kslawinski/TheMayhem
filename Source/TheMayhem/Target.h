// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomObject.h"
#include "Target.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API ATarget : public ACustomObject
{
	GENERATED_BODY()

public:
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void GiveDamage(float damage);

	UStaticMeshComponent* targetMesh;

	float targetHealth;

	
	
};
