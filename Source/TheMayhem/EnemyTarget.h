// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyGunBullet.h"
#include "Target.h"
#include "EnemyTarget.generated.h"

/**
 * 
 */

class APlayerCharacter; // forward declaration of player

UCLASS()
class THEMAYHEM_API AEnemyTarget : public ATarget
{
	GENERATED_BODY()
public:
	AEnemyTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		USceneComponent* gunMoozle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		UStaticMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
		float shootRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
		APlayerCharacter* player;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UStaticMesh* gunMesh;
	UStaticMesh* bazookaMesh;

	FVector enemyLookDirection;

	void Shoot();

	float readyToShootTimer;


	
};
