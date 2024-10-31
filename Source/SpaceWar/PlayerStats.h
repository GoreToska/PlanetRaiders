// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStats.generated.h"


class APlayerShip;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UPlayerStats : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APlayerShip* PlayerShip;

public:
	void ChangeDamage(float Exponent);
	void ChangeHealth(float Exponent);
	void ChangeSpeed(float Exponent);
	void ChangeFireRate(float Exponent);
	void ChangeFlareCooldown(float Exponent);

	float const IncreaseExponent = 1.2;
	float const DecreaseExponent = 0.8;

	float DamageModifier = 1;
	float HealthModifier = 1;
	float SpeedModifier = 1;
	float FireRateModifier = 1;
	float FlareCooldownModifier = 1;
};
