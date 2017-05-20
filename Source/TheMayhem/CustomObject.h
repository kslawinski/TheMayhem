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
	
	void UpdateCollisionBounds();


	bool CheckCollision(FVector testVector, float radius, float height);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionXMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionXMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionYMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionYMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionZMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	float collisionZMax;

private:

};
