// Fill out your copyright notice in the Description page of Project Settings.

#include "TheMayhem.h"
#include "Bullet.h"

/////////////////////////////CUSTOM CODE//////////////////////////////////
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh Component"), false);
	bulletMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	lifeTime = 1.0f;

	for (TActorIterator<ACustomObject> ActorItr(GetWorld()); ActorItr; ++ActorItr) // gather all custom objects from the scene
	{
		if (ActorItr->IsPendingKill())
		{
			continue;
		}



		FString actorName = ActorItr->GetName();

		if (*ActorItr == this || actorName.Contains("Bullet") || actorName.Contains("Rocket")) // skip addding other bullets to the list
		{
			continue;
		}

		ACustomObject* customObject = *ActorItr;
		sceneActors.Add(customObject); // add all custom objects to the list
	}

////////////////////////////////////////////////////////////////////////////////////
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	currentDeltaTime = DeltaTime;

	updateCounter += (DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("Counter is: %f"),updateCounter);

	currentVelocity = direction * speed;

	lifeTime = lifeTime- (DeltaTime * frictionFactor);
	//UE_LOG(LogTemp, Warning, TEXT("bullet life : %f"), lifeTime)

	if (lifeTime <= 0)
	{
		Destroy();
	}

	/////////////////this code is adapted form the lectures///////////////////

	// Apply friction
	float scale = 1.0f - (DeltaTime * frictionFactor);
	speed *= scale;

	FVector NewLocation = GetActorLocation();

	if (!currentVelocity.IsZero()) 
	{
		NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


		SetActorLocation(NewLocation);
	}

	//////////////////////////////////////////////////////////////////////////

	/////////////////////////////CUSTOM CODE//////////////////////////////////

	FRotator bulletRotation = FRotationMatrix::MakeFromX(direction).Rotator();

	SetActorRotation(bulletRotation);

	// Simple collision detection
	if (sceneActors.Num() > 0 )
	{
		if (updateCounter >= 0.1f)
		{
			updateCounter = 0.0f;

			closestActor = FindClosestActor(sceneActors);

			if (closestActor == nullptr) { return; }

			if (closestActor)
			{
				bool isColliding = closestActor->CheckCollision(GetActorLocation(), 1.0f, 2.0f);

				//UE_LOG(LogTemp, Warning, TEXT("colliding with target"))
				FString actorName = closestActor->GetName();

				if (actorName.Contains("Moving"))
				{
					closestActor->UpdateCollisionBounds(); // if the target is a moving target uptate its bounds every frame to check collision
				}

				if (isColliding)
				{


					if (actorName.Contains("Wall"))
					{
						//UE_LOG(LogTemp, Warning, TEXT("bullet colliding with wall"))

						if (IsPendingKill())
						{
							return;
						}
						if (closestActor == nullptr)
						{
							return;
						}

						//sceneActors.Remove(closestActor);
						Destroy();
					}

					if (actorName.Contains("Target"))
					{
						ATarget* closestTarget = Cast<ATarget>(closestActor); // convert it to ATarget

						if (closestTarget == nullptr)
						{
							return;
						}

						if (closestTarget)
						{
							if (closestTarget->IsPendingKill())
							{
								return;
							}

							if (closestTarget == nullptr) { return; }
							closestTarget->GiveDamage(bulletDamage); // damage target 
							//if (closestTarget->GetTargetHealth() <= 0)
							//{
								//sceneActors.Remove(closestTarget);
							//}
							Destroy(); // destroy self
						}
					}
				}
			}
		}
	}
}

void ABullet::BulletFireSetup(FVector direction, float speed)
{
	this->direction = direction;
	this->speed = speed;
}


ACustomObject* ABullet::FindClosestActor(TArray<ACustomObject*> actors)
{
	//ACustomObject* closestActor = nullptr;
	float closestDistanceSqr = (float)1e10;	// Very big number!

	for (int32 i = 0; i < actors.Num(); i++)
	{
		if (actors[i] == nullptr)
		{
			break;
		}

		if (actors[i]->IsPendingKill())
		{
			//actors.Remove(actors[i]);
			break;
		}

		if (actors[i])
		{
			FVector distanceToTarget = (actors[i]->GetActorLocation() - this->GetActorLocation());

			if (distanceToTarget.SizeSquared() < closestDistanceSqr)
			{

				closestDistanceSqr = distanceToTarget.SizeSquared();

				closestActor = actors[i];
			}
		}
	}

	return closestActor;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////