// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CustomObject.generated.h"

UCLASS()
class THEMAYHEM_API ACustomObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* collisionMesh;
	
	void UpdateCollisionBoundaries();

private:
	float collisionXMin;
	float collisionXMax;

	float collisionYMin;
	float collisionYMax;

	float collisionZMin;
	float collisionZMax;
};
