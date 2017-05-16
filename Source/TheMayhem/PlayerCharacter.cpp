// Fill out your copyright notice in the Description page of Project Settings.


#include "TheMayhem.h"
#include "PlayerCharacter.h"





// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	characterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Character Mesh"));
	characterMesh->SetupAttachment(RootComponent);
	characterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Character Camera"));
	characterCamera->SetupAttachment(characterMesh); 


	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(characterMesh);
	weaponMesh->SetRelativeLocation(FVector(90.0f, 30.0f, 40.0f));
	weaponMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
	weaponMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> GunMeshObj(TEXT("StaticMesh'/Game/Geometry/gun.gun'")); // load a mesh from a file
	const ConstructorHelpers::FObjectFinder<UStaticMesh> BazookaMeshObj(TEXT("StaticMesh'/Game/Geometry/bazooka.bazooka'")); // load a mesh from a file
	gunMesh = GunMeshObj.Object;
	bazookaMesh = BazookaMeshObj.Object;

	gunMoozle = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Moozle point"));
	gunMoozle->SetupAttachment(weaponMesh);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GunbooletCount = 0;
	BazookaBooletCount = 0;
	selectedWeapon = ESelectedWeapon::NONE;
	weaponMesh->SetStaticMesh(nullptr);
	weaponIndex++;

	/// DEBUG
	playerHealth = 20;
	GunbooletCount = 50;
	//bGunEquiped = true;
	//bBazookaEquiped = true;
	gunMoozle->SetRelativeLocation(FVector(1.0f, 150.0f, 130.0f));

	for (TActorIterator<ACustomObject> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->IsPendingKill())
		{
			continue;
		}

		ACustomObject* pickup = *ActorItr;
		sceneActors.Add(pickup);
		if (pickup)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found %s"), *pickup->GetName()) // debug message
		}

	}


	if (PlayerUIClass != nullptr)
	{
		
		playerUIwidget = CreateWidget<UPlayerUI>(GetWorld(), PlayerUIClass);

		if (playerUIwidget != nullptr)
		{
			playerUIwidget->AddToViewport();
		}
	}

	RefreshUIWidget();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Direction is: %s"), *direction.ToString());

	currentDeltaTime = DeltaTime;

	currentVelocity = direction * speed;

	// Apply friction
	float scale = 1.0f - (DeltaTime * 0.9f);
	speed *= scale;

	FVector NewLocation = GetActorLocation();

	
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotator(0.0f, 1.0f, 0.0f);

	if (!currentVelocity.IsZero())
	{
			NewLocation = GetActorLocation() + (currentVelocity * DeltaTime);


			SetActorLocation(NewLocation);
	}
	SetActorRotation(CurrentRotation + NewRotation * rotationSpeed * DeltaTime);


	// Simple collision detection
	if (sceneActors.Num() > 0)
	{
		closestActor = FindClosestActor(sceneActors);

		if (closestActor)
		{
			bool isColliding = closestActor->CheckCollision(GetActorLocation(), 1.0f,2.0f);

			if (isColliding)
			{

				//UE_LOG(LogTemp, Warning, TEXT("character is colliding?: %i"), isColliding)
				APickup* closestPickup = Cast<APickup>(closestActor);

				if (closestPickup == nullptr)
				{
					return;
				}

				if (closestPickup != nullptr) // if the closest customObject is a Pickup
				{
					FString actorName = closestPickup->GetName();
					//TODO calapse this into PickItem function
					if (closestPickup->pickupType == EpickupType::CONSUMABLE) // if the pickup I am colliding with is a consumable pickup
					{
						//UE_LOG(LogTemp, Warning, TEXT("Colliding with consumable pickup"))



						if (actorName.Contains("AmmoPickup"))
						{
							GunbooletCount += closestPickup->quantity * 15; // 15 bullets in gun magazine (pack)
							RefreshUIWidget();
							sceneActors.Remove(closestActor);
							closestPickup->Destroy();
						}

						if (actorName.Contains("HealthPickup"))
						{
							playerHealth += closestPickup->quantity * 30; // one healthpack gives 30 HP
							RefreshUIWidget();
							sceneActors.Remove(closestActor);
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
							sceneActors.Remove(closestActor);
							closestPickup->Destroy();
						}
						if (actorName.Contains("BazookaPickup"))
						{
							bBazookaEquiped = true;
							BazookaBooletCount += closestPickup->quantity * 5; // bazooka with 5 rockets
							ChangeWeapon();
							RefreshUIWidget();
							sceneActors.Remove(closestActor);
							closestPickup->Destroy();
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
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &APlayerCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::MoveForward(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorForwardVector() * value;
		speed = 100.0f;
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		direction = GetActorRightVector() * value;
		speed = 100.0f;
	}
}

void APlayerCharacter::RotateRight(float value)
{
	if (value == 1.0f || value == -1.0f)
	{
		rotationSpeed = value * 100.0f;
	}
	else
	{
		rotationSpeed = 0;
	}
}

ACustomObject* APlayerCharacter::FindClosestActor(TArray<ACustomObject*> actors)
{
	ACustomObject* closestActor = nullptr;
	float closestDistanceSqr = (float)1e10;	// Very big number!

	for (int32 i = 0; i < actors.Num(); i++)
	{
		FVector distanceToTarget = (actors[i]->GetActorLocation() - this->GetActorLocation());

		if (distanceToTarget.SizeSquared() < closestDistanceSqr)
		{
			closestDistanceSqr = distanceToTarget.SizeSquared();
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
		bulletInstance->BulletFireSetup(GetActorForwardVector(), 700.0f);
	}

	if (selectedWeapon == ESelectedWeapon::BAZOOKA && BazookaBooletCount > 0)
	{
		BazookaBooletCount--;
		RefreshUIWidget();
		ARocket* rocketInstance = (ARocket*)GWorld->SpawnActor(ARocket::StaticClass());
		rocketInstance->SetActorLocation(gunMoozle->GetComponentLocation());
		rocketInstance->SetActorRotation(GetActorRotation());
		rocketInstance->BulletFireSetup(GetActorForwardVector(), 400.0f);
	}
}

void APlayerCharacter::RefreshUIWidget()
{
	if (playerUIwidget != nullptr)
	{
		playerUIwidget->playerHealth = playerHealth / 100;// 0.5f; // set healthbar to half 50%

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