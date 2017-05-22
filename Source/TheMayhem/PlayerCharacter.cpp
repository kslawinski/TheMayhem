// Fill out your copyright notice in the Description page of Project Settings.


#include "TheMayhem.h"
#include "PlayerCharacter.h"

/////////////////////////////CUSTOM CODE//////////////////////////////////

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

//ROOT
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

//CHARACTER MESH
	characterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Mesh"));
	characterMesh->SetupAttachment(RootComponent);
	characterMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.6f));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> CharacterMeshObj(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'")); // load a mesh from a file
	characterMesh->SetStaticMesh(CharacterMeshObj.Object);

//CAMERA
	characterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
	characterCamera->SetupAttachment(RootComponent);
	characterCamera->SetRelativeLocation(FVector(45.0f, 0.0f, 70.0f));

//WEAPONS
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(RootComponent);
	weaponMesh->SetRelativeLocation(FVector(120.0f, 45.0f, 30.0f));
	weaponMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	weaponMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GunMeshObj(TEXT("StaticMesh'/Game/Geometry/gun.gun'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BazookaMeshObj(TEXT("StaticMesh'/Game/Geometry/bazooka.bazooka'")); // load a mesh from a file
	gunMesh = GunMeshObj.Object;
	bazookaMesh = BazookaMeshObj.Object;

//GunMoozle
	gunMoozle = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Moozle point"));
	gunMoozle->SetupAttachment(weaponMesh);
	gunMoozle->SetRelativeLocation(FVector(0.0f, 174.0f, 125.0f));


}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateCollisionBounds();

	gameOver = false;
	gameWin = false;

	playerHealth = 100;
	playerScore = 0;
	GunbooletCount = 0;
	BazookaBooletCount = 0;
	selectedWeapon = ESelectedWeapon::NONE;
	weaponMesh->SetStaticMesh(nullptr);
	weaponIndex++;

	/// DEBUG
	//GunbooletCount = 50;
	//bGunEquiped = true;
	//bBazookaEquiped = true;
	gunMoozle->SetRelativeLocation(FVector(1.0f, 150.0f, 130.0f));

	for (TActorIterator<ACustomObject> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		FString SceneActorName = ActorItr->GetName();

		if (SceneActorName.Contains("Target"))
		{
			continue;
		}

		ACustomObject* customObject = *ActorItr;
		sceneActors.Add(customObject); // add found custom object to list 

	}

	if (PlayerUIClass != nullptr)
	{
		
		playerUIwidget = CreateWidget<UPlayerUI>(GetWorld(), PlayerUIClass); // create an instance of the UI widget

		if (playerUIwidget != nullptr)
		{
			playerUIwidget->AddToViewport(); // add widget to the screen
		}
	}

	RefreshUIWidget();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	updateCounter += (DeltaTime); // store delta time for future use outside of tick

	currentDeltaTime = DeltaTime;

	currentVelocity = direction * speed;
	/////////////////////////////LECTURE CODE//////////////////////////////////
	// Apply friction
	float scale = 1.0f - (DeltaTime * 0.9f);
	speed *= scale;

	FVector NewLocation = GetActorLocation();

	
	FRotator CurrentRotation = GetActorRotation(); /////////////custom code
	FRotator NewRotation = FRotator(0.0f, 1.0f, 0.0f); //////////////custom code

	if (!currentVelocity.IsZero())
	{
			NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
	}

	//////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////CUSTOM CODE////////////////////////////////////////////
	SetActorRotation(CurrentRotation + NewRotation * rotationSpeed * DeltaTime);

	FRotator CamCurrentElevation = FRotator(characterCamera->GetComponentRotation().Pitch,0.0f,0.0f);
	FRotator NewCamElevation =  FRotator(1.0f, 0.0f, 0.0f);

	characterCamera->SetRelativeRotation(CamCurrentElevation + NewCamElevation * camElevationSpeed * DeltaTime);

	// Simple collision detection
	if (sceneActors.Num() > 0 && updateCounter >= 0.2f)
	{
		updateCounter = 0;

		closestActor = FindClosestActor(sceneActors);

		if (closestActor)
		{
			if (closestActor->IsPendingKill()) // safety check
			{
				return;
			}

			bool isColliding = closestActor->CheckCollision(GetActorLocation(), 70.0f,60.0f);

			if (isColliding)
			{
				FString actorName = closestActor->GetName();

				if (actorName.Contains("Wall"))
				{
					float lastSpeed = speed;
					//UE_LOG(LogTemp, Warning, TEXT("colliding with wall"))
					speed -= lastSpeed * 300.0f * currentDeltaTime;
					FVector lastLocation = GetActorLocation();
					currentVelocity = (FVector(0.0f, 0.0f, 0.0f));
					SetActorLocation(lastLocation);

					return;
				}


				if (closestActor == nullptr)
				{
					return;
				}

				if (closestActor != nullptr) // if the closest customObject is a Pickup
				{
					if (actorName.Contains("Pickup"))
					{
						APickup* closestPickup = Cast<APickup>(closestActor);

						if (closestPickup->pickupType == EpickupType::CONSUMABLE) // if the pickup I am colliding with is a consumable pickup
						{

							if (actorName.Contains("AmmoPickup"))
							{
								GunbooletCount += closestPickup->quantity * 15; // 15 bullets in gun magazine (pack)
								RefreshUIWidget();
								sceneActors.Remove(closestPickup);
								closestPickup->Destroy();
							}

							if (actorName.Contains("HealthPickup"))
							{
								playerHealth += closestPickup->quantity * 30; // one healthpack gives 30 HP
								RefreshUIWidget();
								sceneActors.Remove(closestPickup);
								closestPickup->Destroy();
							}

							if (actorName.Contains("Mine"))
							{
								GiveDamage(closestPickup->quantity);
								sceneActors.Remove(closestPickup);
								RefreshUIWidget();
								closestPickup->Destroy();
							}

						}
						if (closestPickup->pickupType == EpickupType::USABLE) // if the pickup I am colliding with is a consumable pickup
						{
							if (actorName.Contains("GunPickup"))
							{
								bGunEquiped = true;
								GunbooletCount += closestPickup->quantity * 15; // gun with one magazine
								ChangeWeapon();
								RefreshUIWidget();
								sceneActors.Remove(closestPickup);
								closestPickup->Destroy();
							}
							if (actorName.Contains("BazookaPickup"))
							{
								bBazookaEquiped = true;
								BazookaBooletCount += closestPickup->quantity * 5; // bazooka with 5 rockets
								ChangeWeapon();
								RefreshUIWidget();
								sceneActors.Remove(closestPickup);
								closestPickup->Destroy();
							}

							if (actorName.Contains("GoldenPointer"))
							{
								gameWin = true;
								RefreshUIWidget();
								sceneActors.Remove(closestPickup);
								closestPickup->Destroy();
								Destroy();
							}
						}
					}
				}
			}
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateRight", this, &APlayerCharacter::RotateRight);
	PlayerInputComponent->BindAxis("CamElevateUp", this, &APlayerCharacter::CamElevateUp);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &APlayerCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::MoveForward(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorForwardVector();

		speed += FMath::Clamp(value, -1.0f, 1.0f) * 100.0f * currentDeltaTime;
		speed = FMath::Clamp(speed, -200.0f, 500.0f);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorRightVector();
		speed += FMath::Clamp(value, -1.0f, 1.0f) * 100.0f * currentDeltaTime;
		speed = FMath::Clamp(speed, -100.0f, 100.0f);
	}
}

void APlayerCharacter::RotateRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		rotationSpeed = value * 60.0f;
	}
	else
	{
		rotationSpeed = 0;
	}
}

void APlayerCharacter::CamElevateUp(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		camElevationSpeed = value * 60.0f;
		weaponMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, -characterCamera->GetComponentRotation().Pitch)); // adjust weapon mesh rotation to match aiming
	}
	else
	{
		camElevationSpeed = 0;
	}
}

ACustomObject* APlayerCharacter::FindClosestActor(TArray<ACustomObject*> actors)
{
	ACustomObject* closestActor = nullptr;
	float closestDistanceSqr = (float)1e10;

	for (int32 i = 0; i < actors.Num(); i++)
	{


		if (actors[i]->IsPendingKill())
		{
			continue;
		}

		FVector distanceToTarget = (actors[i]->GetActorLocation() - this->GetActorLocation());

		if (distanceToTarget.SizeSquared() < closestDistanceSqr)
		{
			closestDistanceSqr = distanceToTarget.SizeSquared();
			if (actors[i] == nullptr){continue;}
			closestActor = actors[i];
		}
	}

	return closestActor;
}

void APlayerCharacter::ChangeWeapon()
{
		
		switch(weaponIndex)
		{
			case 0:
			{
				UE_LOG(LogTemp, Warning, TEXT("current Weapon is: NONE")) // debug message
				weaponMesh->SetStaticMesh(nullptr);
				selectedWeapon = ESelectedWeapon::NONE;
				break;
			}
			case 1:
			{
				if (bGunEquiped)
				{
					UE_LOG(LogTemp, Warning, TEXT("current Weapon is: Gun")) // debug message
						weaponMesh->SetStaticMesh(gunMesh);
						selectedWeapon = ESelectedWeapon::GUN;

					break;
				}

			}
			case 2:
			{
				if (bBazookaEquiped)
				{

					UE_LOG(LogTemp, Warning, TEXT("current Weapon is: Bazooka")) // debug message
						weaponMesh->SetStaticMesh(bazookaMesh);
					selectedWeapon = ESelectedWeapon::BAZOOKA;

					break;
				}
			}
			default:
			{
				weaponIndex = 0;
			}

		}
		if (weaponIndex > 2)
		{
			weaponIndex = 0;
		}
		else
		weaponIndex++;
		RefreshUIWidget();
}

void APlayerCharacter::Shoot()
{
	if (selectedWeapon == ESelectedWeapon::GUN && GunbooletCount > 0)
	{
		GunbooletCount--;
		RefreshUIWidget();
		AGunBullet* bulletInstance = (AGunBullet*)GWorld->SpawnActor(AGunBullet::StaticClass());
		bulletInstance->SetActorLocation(gunMoozle->GetComponentLocation());
		//TODO Calculate direction
		FVector shootDirection;
		int32 screenSizeX,screenSizeY;
		auto playerCon = GetWorld()->GetFirstPlayerController();

		playerCon->GetViewportSize(screenSizeX, screenSizeY);

		FVector2D aimLocation = FVector2D(screenSizeX * aimPointXLocation, screenSizeY * aimPointYLocation);

		FVector camLocation;// = characterCamera->GetComponentLocation();

		if (playerCon->DeprojectScreenPositionToWorld(aimLocation.X, aimLocation.Y, camLocation, shootDirection))
		{
			bulletInstance->BulletFireSetup(shootDirection, 700.0f);
		}


	}

	if (selectedWeapon == ESelectedWeapon::BAZOOKA && BazookaBooletCount > 0)
	{
		BazookaBooletCount--;
		RefreshUIWidget();
		ARocket* rocketInstance = (ARocket*)GWorld->SpawnActor(ARocket::StaticClass());
		rocketInstance->SetActorLocation(gunMoozle->GetComponentLocation());
		rocketInstance->SetActorRotation(GetActorRotation());

		FVector shootDirection;
		int32 screenSizeX, screenSizeY;
		auto playerCon = GetWorld()->GetFirstPlayerController();

		playerCon->GetViewportSize(screenSizeX, screenSizeY);

		FVector2D aimLocation = FVector2D(screenSizeX * aimPointXLocation, screenSizeY * aimPointYLocation);

		FVector camLocation;// = characterCamera->GetComponentLocation();

		if (playerCon->DeprojectScreenPositionToWorld(aimLocation.X, aimLocation.Y, camLocation, shootDirection))
		{
			rocketInstance->BulletFireSetup(shootDirection, 600.0f);
		}
		
	}
}

void APlayerCharacter::RefreshUIWidget()
{
	if (playerUIwidget != nullptr)
	{
		playerUIwidget->playerHealth = playerHealth / 100;// 0.5f; // set healthbar to half 50%
		playerUIwidget->playerScore = playerScore;
		playerUIwidget->gameOver = gameOver;
		playerUIwidget->gameWin = gameWin;

		if (selectedWeapon == ESelectedWeapon::GUN)
		{
			playerUIwidget->playerBoolets = GunbooletCount;
		}

		if (selectedWeapon == ESelectedWeapon::BAZOOKA)
		{
			playerUIwidget->playerBoolets = BazookaBooletCount;
		}
	}
}


void APlayerCharacter::GiveDamage(float damage)
{
	playerHealth -= damage;
	RefreshUIWidget();

	if (playerHealth <= 0)
	{
		gameOver = true;
		RefreshUIWidget();
		this->Destroy();
	}
}

void APlayerCharacter::GiveScore(int score)
{
	playerScore += score;
	RefreshUIWidget();
}
/////////////////////////////CODE ADAPTED FROM LECTURES//////////////////////////////////

void APlayerCharacter::UpdateCollisionBounds()
{
	//UE_LOG(LogTemp, Warning, TEXT("collision bounds updated"))
	FVector origin, bounds;

	GetActorBounds(false, origin, bounds);

	collisionXMin = origin.X - bounds.X;
	collisionXMax = origin.X + bounds.X;
	collisionYMin = origin.Y - bounds.Y;
	collisionYMax = origin.Y + bounds.Y;
	collisionZMin = origin.Z - bounds.Z;
	collisionZMax = origin.Z + bounds.Z;

}

bool APlayerCharacter::CheckCollision(FVector testVector, float radius, float height)
{
	/////////////////////////////CUSTOM CODE modified check collision function //////////////////////////////////

	bool isColliding = false;

	bool collidingX = false;
	bool collidingY = false;
	bool collidingZ = false;


	if (((testVector.X + radius) >= collisionXMin) && ((testVector.X - radius) <= collisionXMax))
	{
		collidingX = true;
	}

	if (((testVector.Y + radius) >= collisionYMin) && ((testVector.Y - radius) <= collisionYMax))
	{
		collidingY = true;
	}

	if ((testVector.Z) >= collisionZMin && ((testVector.Z - height) <= collisionZMax + height))
	{
		collidingZ = true;
	}

	if (collidingX && collidingY && collidingZ)
	{
		isColliding = true;
	}

	return isColliding;
}

///////////////////////////////////////////////////////////////////////////////////////////////