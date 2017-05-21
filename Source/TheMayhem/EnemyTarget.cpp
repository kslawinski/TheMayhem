// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "EnemyTarget.h"
#include "PlayerCharacter.h"



AEnemyTarget::AEnemyTarget()
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(RootComponent);
	weaponMesh->SetRelativeLocation(FVector(70.0f, 45.0f, 30.0f));
	weaponMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	weaponMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GunMeshObj(TEXT("StaticMesh'/Game/Geometry/gun.gun'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BazookaMeshObj(TEXT("StaticMesh'/Game/Geometry/bazooka.bazooka'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyTargetMeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	gunMesh = GunMeshObj.Object;
	bazookaMesh = BazookaMeshObj.Object;

	targetMesh->SetStaticMesh(EnemyTargetMeshObj.Object);

	gunMoozle = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Moozle point"));
	gunMoozle->SetupAttachment(weaponMesh);

	weaponMesh->SetStaticMesh(gunMesh); // for now

	targetMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	targetMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.6f));
	collisionMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.6f));
}

// Called when the game starts or when spawned
void AEnemyTarget::BeginPlay()
{
	Super::BeginPlay();

	readyToShootTimer = 0;
	shootRate = 2.0f;


	UE_LOG(LogTemp, Warning, TEXT("Start Called"))

		Shoot(); // test shoot
}

// Called every frame
void AEnemyTarget::Tick(float DeltaTime)
{
	updateCounter += (DeltaTime);

	readyToShootTimer += (DeltaTime);

	if (player && updateCounter >= 0.4f)
	{
		updateCounter = 0;
		float distanceToPlayer = FVector::Distance(player->GetActorLocation(), this->GetActorLocation());

		if (distanceToPlayer <= 1700.0f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("tICK"))

			FRotator currentRotation = GetActorRotation();

			enemyLookDirection = (player->GetActorLocation() - this->GetActorLocation()).GetSafeNormal();
			enemyLookDirection.Z = 0.0f;

			//UE_LOG(LogTemp, Warning, TEXT("Look Direction is %s"), *enemyLookDirection.ToString())

			FRotator newEnemyRot = FRotationMatrix::MakeFromX(enemyLookDirection).Rotator();

			//SetActorRotation(currentRotation + newEnemyRot * 2.0f * DeltaTime);

			SetActorRotation(newEnemyRot);



			if (readyToShootTimer >= shootRate)
			{
				readyToShootTimer = 0;
				Shoot();
			}
		}
	}
}

void AEnemyTarget::Shoot()
{
	AEnemyGunBullet* bulletInstance = (AEnemyGunBullet*)GWorld->SpawnActor(AEnemyGunBullet::StaticClass());
	bulletInstance->SetActorLocation(gunMoozle->GetComponentLocation());

	//FVector shootDirection = enemyLookDirection;

	bulletInstance->BulletFireSetup(GetActorForwardVector(), 700.0f);
	bulletInstance->SetPlayer(player);
}


