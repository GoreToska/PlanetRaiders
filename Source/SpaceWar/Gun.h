// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AProjectileBase;

UCLASS()
class SPACEWAR_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

	void FireShot(float DamageModifier);
	void PerformShot();
	void Equip();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChose);

	UPROPERTY(BlueprintAssignable)
	FOnChose OnEquipped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	FTimerHandle ShootingTimerHandle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 100;
	UPROPERTY(EditAnywhere)
	float Distance = 1000;

	float SavedDamageModifier = 1;
};
