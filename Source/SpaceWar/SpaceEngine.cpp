// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEngine.h"

#include "HealthComponent.h"

// Sets default values
ASpaceEngine::ASpaceEngine()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ASpaceEngine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpaceEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceEngine::HandleDeath()
{
	OnDead.Broadcast();
	Destroy();
}
