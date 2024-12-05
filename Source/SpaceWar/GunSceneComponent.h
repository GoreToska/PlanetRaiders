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
	void LoadAmmo();
	void SpendAmmo();
	void PlayShotSound(USceneComponent* ActorRoot);
	UFUNCTION(BlueprintCallable)
	int GetAmmo();
	FVector2D GetFirstCrosshairPosition() const;
	FVector2D GetSecondCrosshairPosition() const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulletStatus, int, NewAmmoValue);

	UPROPERTY()
	UPlayerStats* PlayerStats;
	UPROPERTY()
	FTimerHandle ShootingTimerHandle;
	UPROPERTY()
	FTimerHandle LoadingTimerHandle;
	UPROPERTY(EditAnywhere)
	FVector2D Spread = FVector2D(1, 1);
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 100;
	UPROPERTY(EditAnywhere)
	float Distance = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxAmmo = 40;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeToLoadAmmo = 0.5;
	UPROPERTY(BlueprintReadOnly)
	float LoadingTimePassed = 0;
	UPROPERTY(BlueprintReadOnly)
	int CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CrosshairTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UI_Image;
	UPROPERTY(EditAnywhere)
	USoundBase* ShotSound;
	UPROPERTY(EditAnywhere)
	USoundBase* EmptySound;

	UPROPERTY(BlueprintAssignable)
	FBulletStatus OnBulletCountChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OnShotFired();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
};
