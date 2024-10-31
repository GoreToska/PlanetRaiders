// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipBase.h"

#include "DodgeComponent.h"
#include "HealthComponent.h"
#include "PlayerStats.h"
#include "ProjectileBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpaceShipBase::ASpaceShipBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComponent->SetupAttachment(RootComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);

	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetEnableGravity(false);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	PlayerStats = CreateDefaultSubobject<UPlayerStats>(TEXT("Player Stats"));
	DodgeComponent = CreateDefaultSubobject<UDodgeComponent>(TEXT("Dodge Component"));
	BlasterFireSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Blaster Fire Socket"));
	BlasterFireSocket->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void ASpaceShipBase::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentHit.AddDynamic(this, &ASpaceShipBase::OnCollide);
}

void ASpaceShipBase::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void ASpaceShipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASpaceShipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UStaticMeshComponent& ASpaceShipBase::GetMesh()
{
	return *StaticMeshComponent;
}

void ASpaceShipBase::SetGun()
{
	/*if (CurrentGunIndex < 0)
		CurrentGunIndex = Guns.Num() - 1;
	if (CurrentGunIndex > Guns.Num() - 1)
		CurrentGunIndex = 0;

	CurrentGun = Guns[CurrentGunIndex];
	CurrentGun->Equip();*/
}

void ASpaceShipBase::FireBlasterShot()
{
	FVector Location = BlasterFireSocket->GetComponentLocation();
	FRotator Rotation = BlasterFireSocket->GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UE_LOG(LogTemp, Display, TEXT("Shot!"));

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		BlasterProjectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(PlayerStats->DamageModifier);
	}
}
