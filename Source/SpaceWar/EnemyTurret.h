// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "GameFramework/Pawn.h"
#include "EnemyTurret.generated.h"

class UHealthComponent;
class UBoxComponent;
class APlayerShip;
class AProjectileBase;

UCLASS()
class SPACEWAR_API AEnemyTurret : public APawn, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyTurret();

	UPROPERTY(EditAnywhere)
	USoundBase* ShotSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USceneComponent* TurretRoot;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretBase;
	UPROPERTY(EditAnywhere)
	USceneComponent* TurretHeadSocket;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretHead;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* FireSocket;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere)
	FVector2D Spread = FVector2D(1, 1);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 800;
	UPROPERTY(EditAnywhere)
	float AttackDistance = 1000;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
	float ProjectileSpeed;

	UPROPERTY()
	APlayerShip* PlayerShip;
	UFUNCTION(BlueprintCallable)
	void RotateTowardsPlayer();

	UPROPERTY(EditAnywhere)
	float BurstShotsCount = 5;
	UPROPERTY(EditAnywhere)
	float MinBurstCooldown = 3;
	UPROPERTY(EditAnywhere)
	float MaxBurstCooldown = 10;
	float CurrentShot = 0;

	void ShotCooldownEvent();
	void BurstCooldownEvent();

	UPROPERTY()
	FTimerHandle ShotTimerHandle;
	UPROPERTY()
	FTimerHandle BurstTimerHandle;

	UFUNCTION(BlueprintCallable)
	bool CheckDistanceToPlayer();
	UFUNCTION(BlueprintCallable)
	FVector GetPredictedVector();
	UFUNCTION(BlueprintCallable)
	void RotateTowardsPredictedPosition();
	UFUNCTION()
	virtual void SetupProjectile(FVector Location, FRotator Rotation);
	UPROPERTY(EditAnywhere)
	float IncreaseExponent = 0.2;
	int CurrentUpgrade;

	UFUNCTION()
	void Upgrade(int Upgrade);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void FireShot();

	virtual void HandleDeath() override;
};
