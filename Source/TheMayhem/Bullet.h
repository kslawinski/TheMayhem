// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomObject.h"
#include "Bullet.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API ABullet : public ACustomObject
{
	GENERATED_BODY()

public:
	ABullet();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* bulletMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BulletFireSetup(FVector direction,float speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	float frictionFactor = 0.2f;

private:
	FVector currentVelocity;
	FVector direction;
	float speed;


	float currentDeltaTime;
	FRotator rotation;
	
	
};
