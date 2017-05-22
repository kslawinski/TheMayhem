// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "EnemyGunBullet.h"
#include "PlayerCharacter.h"

/////////////////////////////CUSTOM CODE//////////////////////////////////
AEnemyGunBullet::AEnemyGunBullet()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/Enemybullet.Enemybullet'")); // load a mesh from a file
	bulletMesh->SetStaticMesh(MeshObj.Object);

	collisionMesh->SetWorldScale3D(FVector(0.03f, 0.03f, 0.03f));
	bulletMesh->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));

	bulletDamage = 100.0f; // for test
}

// Called every frame
void AEnemyGunBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("bullet life : %f"), lifeTime)
		UpdateCollisionBounds(); // update bounds to make sure the collision is updated
		player->UpdateCollisionBounds();
		FVector playerLocation = player->GetActorLocation();


		if (CheckCollision(player->GetActorLocation(),100.0f ,100.0f))
		{
			if (this->IsPendingKill()) // safety check
			{
				return;
			}

			UE_LOG(LogTemp, Warning, TEXT("colliding with player enemy bullet"))
			player->GiveDamage(bulletDamage);

			Destroy();
		}
	}
}

void AEnemyGunBullet::SetPlayer(APlayerCharacter * player)
{
	this->player = player;
}
/////////////////////////////////////////////////////////////////////////