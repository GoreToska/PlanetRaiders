// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipBase.generated.h"

class AHomingProjectile;
class USpaceShipMovementComponent;
class URegeneratableHealthComponent;
class UGunSceneComponent;
class UDodgeComponent;
class UPlayerStats;
class AStatsManager;
class UBoxComponent;
class AProjectileBase;

UCLASS()
class SPACEWAR_API ASpaceShipBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipBase();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChose, UGunSceneComponent*, NewGun, UGunSceneComponent*,
	                                             PreviouseGun);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFollowedRocketCountChanged);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	URegeneratableHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerStats* PlayerStats;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDodgeComponent* DodgeComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UGunSceneComponent* BlasterGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGunSceneComponent* RocketGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGunSceneComponent* CurrentGun;
	UPROPERTY(EditAnywhere)
	USpaceShipMovementComponent* MovementComponent;
	UPROPERTY(EditAnywhere)
	USoundBase* GunChangedSound;
	UPROPERTY(EditAnywhere)
	USoundBase* RocketAlarmSound;

	UPROPERTY()
	UAudioComponent* AlarmSpawnedSound;

	UPROPERTY
	(BlueprintAssignable)
	FOnChose OnEquipped;
	UPROPERTY(BlueprintAssignable)
	FOnFollowedRocketCountChanged OnRocketFollowAdded;
	UPROPERTY(BlueprintAssignable)
	FOnFollowedRocketCountChanged OnRocketFollowRemoved;

	void AddHomingRocket(AHomingProjectile* Projectile);
	void RemoveHomingRocket(AHomingProjectile* Projectile);

	UFUNCTION(BlueprintCallable)
	int RocketsFollowedCount();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> BlasterProjectile;
	UPROPERTY(EditAnywhere)
	UParticleSystem* FlareParticles;

	UPROPERTY()
	FTimerHandle BlasterShootingTimerHandle;
	UPROPERTY()
	FTimerHandle FlareTimerHandle;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	float FlareCooldown = 10;
	UPROPERTY(EditAnywhere)
	float CollideDamage = 100;

	UPROPERTY()
	TArray<AHomingProjectile*> ProjectilesAfterPlayer;

	UFUNCTION()
	virtual void OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                       FVector NormalImpulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UStaticMeshComponent& GetMesh();
	void SetBlasterGun();
	void SetRocketGun();
	void FireCurrentGunShot();
};
