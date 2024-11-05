// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipBase.h"

#include "DodgeComponent.h"
#include "GunSceneComponent.h"
#include "PlayerStats.h"
#include "RegeneratableHealthComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpaceShipBase::ASpaceShipBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(BoxComponent);
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetEnableGravity(false);

	HealthComponent = CreateDefaultSubobject<URegeneratableHealthComponent>(TEXT("Health Component"));
	PlayerStats = CreateDefaultSubobject<UPlayerStats>(TEXT("Player Stats"));
	DodgeComponent = CreateDefaultSubobject<UDodgeComponent>(TEXT("Dodge Component"));
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

void ASpaceShipBase::SetBlasterGun()
{
	if (CurrentGun == BlasterGun)
		return;

	OnEquipped.Broadcast(BlasterGun, CurrentGun);
	CurrentGun = BlasterGun;
}

void ASpaceShipBase::SetRocketGun()
{
	if (CurrentGun == RocketGun)
		return;

	OnEquipped.Broadcast(RocketGun, CurrentGun);
	CurrentGun = RocketGun;
}

void ASpaceShipBase::FireCurrentGunShot()
{
	CurrentGun->PerformShot();
}
