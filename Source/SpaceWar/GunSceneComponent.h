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
	void LoadAmmo();
	void SpendAmmo();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChose);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletStatus, int, NewAmmoValue);

	UPROPERTY()
	UPlayerStats* PlayerStats;
	UPROPERTY()
	FTimerHandle ShootingTimerHandle;
	UPROPERTY()
	FTimerHandle LoadingTimerHandle;
	UPROPERTY(EditAnywhere)
	int MaxAmmo = 40;
	UPROPERTY(EditAnywhere)
	float TimeToLoadAmmo = 0.5;
	int CurrentAmmo;

	UPROPERTY(BlueprintAssignable)
	FOnChose OnEquipped;
	UPROPERTY(BlueprintAssignable)
	FBulletStatus OnBulletCountChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 100;
	UPROPERTY(EditAnywhere)
	float Distance = 1000;
};
