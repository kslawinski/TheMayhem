// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CustomObject.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API AWall : public ACustomObject
{
	GENERATED_BODY()
	
public:
	AWall();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UStaticMeshComponent* wallMesh;
	
};
