// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunComponent.generated.h"


class AProjectileBase;
class UPlayerStats;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UPlayerStats* PlayerStats;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectileBase> Projectile;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* FireSocket;
	
	UPROPERTY(EditAnywhere)
	float FireSpeedPerSec = 100;

public:
	virtual void FireShot();
	virtual void PerformShot();
	virtual void Equip();

	UPROPERTY()
	FTimerHandle ShootingTimerHandle;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChose);

	UPROPERTY(BlueprintAssignable)
	FOnChose OnEquipped;
};
