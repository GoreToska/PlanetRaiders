// Fill out your copyright notice in the Description page of Project Settings.


#include "CargoCarrier.h"
#include "HealthComponent.h"
#include "PlayerInventory.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACargoCarrier::ACargoCarrier()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SetRootComponent(StaticMesh);
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	BoxCollider->SetupAttachment(StaticMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void ACargoCarrier::BeginPlay()
{
	Super::BeginPlay();

	Inventory = UGameplayStatics::GetPlayerPawn(this, 0)
		->GetComponentByClass<UPlayerInventory>();
}

// Called every frame
void ACargoCarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveForward(DeltaTime);
}

// Called to bind functionality to input
void ACargoCarrier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACargoCarrier::HandleDeath()
{
	Destroy();
	GetReward();
}

void ACargoCarrier::GetReward()
{
	if (!Inventory)
		return;

	Inventory->AddItem(CarryItem.GetDefaultObject());
}

void ACargoCarrier::MoveForward(float deltaTime)
{
	AddActorWorldOffset(GetActorForwardVector() * MoveSpeed * deltaTime, true);
}
