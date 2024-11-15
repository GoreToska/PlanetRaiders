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

	UFUNCTION()
	void ClearProjectileHomingTarget();
	
protected:
	virtual void BeginPlay() override;
	virtual void HandleHit() override;
	virtual void DestroyProjectile() override;
	
private:
	UPROPERTY()
	APlayerShip* PlayerShip;
};
