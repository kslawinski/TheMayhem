// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerUI.generated.h"

/**
 * Class allowing for C++ and blueprnt widget communication
 */
UCLASS()
class THEMAYHEM_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	float playerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	int32 playerBoolets;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	int32 playerScore;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	bool gameOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	bool gameWin;
	
};
