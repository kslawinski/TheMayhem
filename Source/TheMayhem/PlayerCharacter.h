// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PlayerUI.h"
#include "Blueprint/UserWidget.h"
#include "Pickup.h"
#include "GunBullet.h"
#include "Rocket.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"



UENUM(BlueprintType)
enum class ESelectedWeapon : uint8
{
	GUN,
	BAZOOKA,
	NONE
};

UCLASS()
class THEMAYHEM_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

private:
	bool gameOver;

	float playerHealth;
	int32  playerScore;

	FVector currentVelocity;
	FVector direction;
	float speed;
	float rotationSpeed;
	float camElevationSpeed;
	float currentDeltaTime;

	FRotator rotation;

	bool bGunEquiped, bBazookaEquiped;
	int32 weaponIndex;
	ESelectedWeapon selectedWeapon;

	float aimPointXLocation = 0.5f;
	float aimPointYLocation = 0.5f;
	void RefreshUIWidget();
	
public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	int32 GunbooletCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
	int32 BazookaBooletCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionXMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionXMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionYMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionYMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionZMin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEBUG")
		float collisionZMax;

	void GiveDamage(float damage);

	void GiveScore(int score);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void RotateRight(float value);

	void CamElevateUp(float value);

	void UpdateCollisionBounds();

	bool CheckCollision(FVector testVector, float radius, float height);

	ACustomObject* FindClosestActor(TArray <ACustomObject*> actors);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SETUP")
	UStaticMeshComponent* characterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SETUP")
	UStaticMeshComponent* weaponMesh;
	UStaticMesh* gunMesh;
	UStaticMesh* bazookaMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SETUP")
	USceneComponent* gunMoozle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CAMERA")
	UCameraComponent* characterCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	ACustomObject* closestActor;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DEBUG")
	TArray <ACustomObject*> sceneActors;

	//The widget class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SETUP")
		TSubclassOf<UPlayerUI> PlayerUIClass;

	//The widget instance
	UPROPERTY()
		UPlayerUI* playerUIwidget;

private:
	//FIRING
	void ChangeWeapon();
	void Shoot();

	
};
