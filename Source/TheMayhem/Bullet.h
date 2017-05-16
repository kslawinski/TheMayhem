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
	
	
};
