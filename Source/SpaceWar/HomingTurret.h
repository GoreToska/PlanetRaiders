// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyTurret.h"
#include "HomingTurret.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWAR_API AHomingTurret : public AEnemyTurret
{
	GENERATED_BODY()

protected:
	virtual void SetupProjectile(FVector Location, FRotator Rotation) override;
};
