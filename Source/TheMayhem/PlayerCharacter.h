// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Pickup.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class ESelectedWeapon : uint8
{
	GUN,
	BAZOOKA
};

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

	ESelectedWeapon selectedWeapon;

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	int32 GunbooletCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	int32 BazookaBooletCount;

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

	ACustomObject* FindClosestActor(TArray <ACustomObject*> actors);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* characterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* weaponMesh;
	UStaticMesh* gunMesh;
	UStaticMesh* bazookaMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* characterCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	ACustomObject* closestActor;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	TArray <ACustomObject*> sceneActors;

private:
	void ChangeWeapon();
};
