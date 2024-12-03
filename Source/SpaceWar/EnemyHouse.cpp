// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHouse.h"

#include "HealthComponent.h"
#include "SpaceGameInstance.h"
#include "SpaceGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AEnemyHouse::Upgrade(int Value)
{
	CurrentUpgrade = Value;
	HealthComponent->SetNewMaxHealth(HealthComponent->MaxHP * (1 + IncreaseExponent));
}

// Called when the game starts or when spawned
void AEnemyHouse::BeginPlay()
{
	Super::BeginPlay();

	CurrentUpgrade = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetCurrentUpgrade();
	Upgrade(CurrentUpgrade);
	Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->OnUpgraded.AddDynamic(
		this, &AEnemyHouse::Upgrade);
}

// Called every frame
void AEnemyHouse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyHouse::HandleDeath()
{
	//Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetGameInstance()->OnUpgraded.RemoveDynamic(
	//	this, &AEnemyHouse::Upgrade);
	OnBuildingDestroyed.Broadcast(this);
	Destroy();
}
