// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GunSceneComponent.generated.h"


class UGunSocket;
class AProjectileBase;
class UPlayerStats;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UGunSceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGunSceneComponent();

	void FireShot();
	void PerformShot();
	void Equip();

	UPROPERTY()
	FTimerHandle ShootingTimerHandle;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChose);

	UPROPERTY(BlueprintAssignable)
	FOnChose OnEquipped;

	UPROPERTY()
	UPlayerStats* PlayerStats;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
	UPROPERTY(EditAnywhere)
	UGunSocket* GunSocket01;
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 100;
	UPROPERTY(EditAnywhere)
	float Distance = 1000;
};
