// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats.h"

#include "PlayerShip.h"

// Sets default values for this component's properties
UPlayerStats::UPlayerStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerStats::BeginPlay()
{
	Super::BeginPlay();

	PlayerShip = Cast<APlayerShip>(GetOwner());
	// ...
}

void UPlayerStats::ChangeDamage(float Exponent)
{
	DamageModifier *= Exponent;
	PlayerShip->UpdateStats();
}

void UPlayerStats::ChangeHealth(float Exponent)
{
	HealthModifier *= Exponent;
	PlayerShip->UpdateStats();
}

void UPlayerStats::ChangeSpeed(float Exponent)
{
	SpeedModifier *= Exponent;
	PlayerShip->UpdateStats();
}

void UPlayerStats::ChangeFireRate(float Exponent)
{
	FireRateModifier *= Exponent;
	PlayerShip->UpdateStats();
}

void UPlayerStats::ChangeFlareCooldown(float Exponent)
{
	FlareCooldownModifier *= Exponent;
	PlayerShip->UpdateStats();
}
