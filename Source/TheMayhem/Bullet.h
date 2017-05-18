// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Target.h"
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

	ACustomObject * FindClosestActor(TArray<ACustomObject*> actors);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	float frictionFactor = 0.2f;
	float bulletDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	TArray <ACustomObject*> sceneActors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	ACustomObject* closestActor;

private:
	FVector currentVelocity;
	FVector direction;
	float speed;
	float lifeTime;



	float currentDeltaTime;
	FRotator rotation;
	
	
};
