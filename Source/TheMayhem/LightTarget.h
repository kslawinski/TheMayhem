// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Target.h"
#include "LightTarget.generated.h"

/**
 * 
 */
UCLASS()
class THEMAYHEM_API ALightTarget : public ATarget
{
	GENERATED_BODY()

		ALightTarget();
	
private:
	UPointLightComponent* lightComponent;
	
};
