// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CustomObject.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UENUM(BlueprintType)
enum class EpickupType : uint8
{
	CONSUMABLE,
	USABLE
};

UCLASS()
class THEMAYHEM_API APickup : public ACustomObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	//TODO ENUM CONSUMABLE, USABLE
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Setup")
		EpickupType pickupType;

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Setup")
	int32 quantity;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		UStaticMeshComponent* pickupMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Setup")
		float rotationSpeed = 100.0f;
private:

	
};
