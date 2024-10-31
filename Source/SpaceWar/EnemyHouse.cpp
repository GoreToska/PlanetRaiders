// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHouse.h"

#include "HealthComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemyHouse::AEnemyHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(BoxComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AEnemyHouse::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyHouse::HandleDeath()
{
	Destroy();
}
