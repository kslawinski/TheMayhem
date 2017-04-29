// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Pickup.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class THEMAYHEM_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

private:
	FVector currentVelocity;
	FVector direction;
	float speed;
	float rotationSpeed;
	float currentDeltaTime;

	FRotator rotation;



public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void RotateRight(float value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* characterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* characterCamera;

		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	TArray <APickup*> pickups;
};
