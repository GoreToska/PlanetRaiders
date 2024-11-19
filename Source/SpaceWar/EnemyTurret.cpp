// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTurret.h"

#include "HealthComponent.h"
#include "PlayerShip.h"
#include "ProjectileBase.h"
#include "SpaceGameMode.h"
#include "WorldDifficulty.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyTurret::AEnemyTurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TurretRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Root"));
	//SetRootComponent(TurretRoot);

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Base"));
	SetRootComponent(TurretBase);

	TurretHeadSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Turret Head Socket"));
	TurretHeadSocket->SetupAttachment(TurretBase);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComponent->SetupAttachment(TurretHeadSocket);

	TurretHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Head"));
	TurretHead->SetupAttachment(TurretHeadSocket);

	FireSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Socket"));
	FireSocket->SetupAttachment(TurretHead);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AEnemyTurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerShip = Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(this, 0));

	CurrentUpgrade = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetWorldDifficulty()->
		GetCurrentUpgrade();

	Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetWorldDifficulty()->OnUpgraded.AddDynamic(
		this, &AEnemyTurret::Upgrade);
}

void AEnemyTurret::RotateTowardsPlayer()
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TurretHeadSocket->GetComponentLocation(),
	                                                                 PlayerShip->GetActorLocation());
	if (PlayerShip)
		TurretHeadSocket->SetWorldRotation(LookAtRotation);
}

void AEnemyTurret::Upgrade(int Upgrade)
{
	CurrentUpgrade = Upgrade;
	HealthComponent->SetNewMaxHealth(HealthComponent->MaxHP * (1 + IncreaseExponent));
}

// Called every frame
void AEnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//RotateTowardsPredictedPosition();

	RotateTowardsPlayer();

	if (GetWorld()->GetTimerManager().IsTimerActive(BurstTimerHandle))
		return;

	if (!CheckDistanceToPlayer())
		return;

	FireShot();

	if (CurrentShot >= BurstShotsCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &AEnemyTurret::BurstCooldownEvent,
		                                       BurstCooldown, false);
	}
}

// Called to bind functionality to input
void AEnemyTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyTurret::FireShot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShotTimerHandle))
		return;

	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &AEnemyTurret::ShotCooldownEvent, 60 / FireRate,
	                                       false);

	FVector Location = FireSocket->GetComponentLocation();
	FRotator Rotation = FireSocket->GetComponentRotation();

	SetupProjectile(Location, Rotation);
	UGameplayStatics::SpawnSoundAtLocation(this, ShotSound, GetActorLocation());
}

void AEnemyTurret::HandleDeath()
{
	Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetWorldDifficulty()->OnUpgraded.RemoveDynamic(
		this, &AEnemyTurret::Upgrade);

	Destroy();
}

void AEnemyTurret::ShotCooldownEvent()
{
	CurrentShot++;
}

void AEnemyTurret::BurstCooldownEvent()
{
	CurrentShot = 0;
	GetWorld()->GetTimerManager().ClearTimer(BurstTimerHandle);
}

bool AEnemyTurret::CheckDistanceToPlayer()
{
	if (FVector::Distance(GetActorLocation(), PlayerShip->GetActorLocation()) <= AttackDistance)
		return true;

	return false;
}

FVector AEnemyTurret::GetPredictedVector()
{
	FVector PlayerLocation = PlayerShip->GetActorLocation();
	FVector PlayerForwardVector = -PlayerShip->GetActorForwardVector();
	FVector PredictedVector = PlayerLocation - PlayerForwardVector * PlayerShip->GetCurrentSpeed();

	return PredictedVector;
}

void AEnemyTurret::RotateTowardsPredictedPosition()
{
	FVector NewRotation = GetPredictedVector();
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TurretHeadSocket->GetComponentLocation(),
	                                                                 NewRotation);
	TurretHeadSocket->SetWorldRotation(LookAtRotation);
}

void AEnemyTurret::SetupProjectile(FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Rotation.Pitch += FMath::RandRange(-Spread.X, Spread.X);
	Rotation.Yaw += FMath::RandRange(-Spread.Y, Spread.Y);

	AProjectileBase* ProjectileBase = GetWorld()->
		SpawnActor<AProjectileBase>(Projectile, Location, Rotation, SpawnInfo);

	if (!this || !ProjectileBase)
		return;

	ProjectileBase->SetOwner(this);
	ProjectileBase->SetProjectileDamageModifier(1 + (CurrentUpgrade - 1) * IncreaseExponent);
}
