// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomObject.h"
#include "Target.generated.h"

/**
 * 
 */
class APlayerCharacter;

UCLASS()
class THEMAYHEM_API ATarget : public ACustomObject
{
	GENERATED_BODY()

public:
	ATarget();

	void GiveDamage(float damage);
	float GetTargetHealth();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
		APlayerCharacter* player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UStaticMeshComponent* targetMesh;

	float targetHealth;

	
	
};
