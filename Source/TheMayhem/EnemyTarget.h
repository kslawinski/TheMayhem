// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Target.h"
#include "EnemyTarget.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API AEnemyTarget : public ATarget
{
	GENERATED_BODY()
	
private:


	UStaticMesh* gunMesh;
	UStaticMesh* bazookaMesh;


	void Shoot();
	
public:
	AEnemyTarget();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	USceneComponent* gunMoozle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* weaponMesh;
	
};
