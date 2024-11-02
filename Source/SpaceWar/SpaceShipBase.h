// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipBase.generated.h"

class UGunSceneComponent;
class UDodgeComponent;
class UPlayerStats;
class AStatsManager;
class UHealthComponent;
class UBoxComponent;
class AProjectileBase;

UCLASS()
class SPACEWAR_API ASpaceShipBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerStats* PlayerStats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDodgeComponent* DodgeComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> BlasterProjectile;
	UPROPERTY(EditAnywhere)
	UParticleSystem* FlareParticles;

	//UPROPERTY(EditAnywhere)
	//USceneComponent* BlasterFireSocket;

	UPROPERTY(EditAnywhere)
	UGunSceneComponent* BlasterGun;

	UPROPERTY()
	FTimerHandle BlasterShootingTimerHandle;
	UPROPERTY()
	FTimerHandle FlareTimerHandle;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1500.f;
	UPROPERTY(EditAnywhere)
	float MinSpeed = 600.f;
	UPROPERTY(EditAnywhere)
	float RotationPower = 5.f;
	UPROPERTY(EditAnywhere)
	float TurnSpeed = 1.5f;
	UPROPERTY(EditAnywhere)
	float AimingTurnSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
	float InterpolationSpeed = 10;
	UPROPERTY(EditAnywhere)
	float SpeedChangingMultiplier = 400;
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 600;
	UPROPERTY(EditAnywhere)
	float FlareCooldown = 10;
	UPROPERTY(EditAnywhere)
	float CollideDamage = 100;
	float CurrentSpeed;

	UFUNCTION()
	virtual void OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                       FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UStaticMeshComponent& GetMesh();
	void SetGun();
	void FireBlasterShot();
};
