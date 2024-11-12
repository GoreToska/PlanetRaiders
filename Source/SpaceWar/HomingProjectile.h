// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "HomingProjectile.generated.h"

class APlayerShip;
/**
 * 
 */
UCLASS()
class SPACEWAR_API AHomingProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	void SetProjectileHomingTarget(APlayerShip* playerShip);
	void StartProjectileTimer();

	UFUNCTION()
	void ClearProjectileHomingTarget();
	
protected:
	UPROPERTY()
	FTimerHandle DestructionTimer;
	UPROPERTY(EditAnywhere)
	float TimeToLive = 10.f;
	UPROPERTY(EditAnywhere)
	UParticleSystem* DestroyParticles;
	UFUNCTION()
	void DestroyProjectile();
	virtual void BeginPlay() override;
	virtual void HandleHit() override;

private:
	UPROPERTY()
	APlayerShip* PlayerShip;
};
