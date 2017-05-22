// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Target.h"
#include "PlayerCharacter.h"

/////////////////////////////CUSTOM CODE//////////////////////////////////
// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<APlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr) // Find Player
	{
		/*	if (*ActorItr == nullptr)
		{
		continue;
		}*/
		FString actorName = *ActorItr->GetName();

		if (actorName.Contains("Player"))
		{
			player = *ActorItr;
			break;
		}
	}
}

ATarget::ATarget()
{
	targetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target Mesh"), false);
	targetMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Geometry/AimCircle.AimCircle'")); // load a mesh from a file
	targetMesh->SetStaticMesh(MeshObj.Object);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> TargetMeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cylinder.Cylinder'")); // load a mesh from a file


	targetMesh->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	targetMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	collisionMesh->SetStaticMesh(TargetMeshObj.Object);
	collisionMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	collisionMesh->SetWorldScale3D(FVector(2.2f, 1.2f, 2.2f));

	targetHealth = 100.0f;
}

void ATarget::GiveDamage(float damage)
{
	targetHealth -= damage;

	if (targetHealth <= damage)
	{
		player->GiveScore(10);
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Destroying target"))
	}
}

float ATarget::GetTargetHealth()
{
	return targetHealth;
}

///////////////////////////////////////////////////////////////////////////////////