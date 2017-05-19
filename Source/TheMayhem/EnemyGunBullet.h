// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "EnemyGunBullet.generated.h"

/**
 * 
 */
class APlayerCharacter;

UCLASS()
class THEMAYHEM_API AEnemyGunBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	AEnemyGunBullet();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	APlayerCharacter* player;

	void SetPlayer(APlayerCharacter* player);
	
};
