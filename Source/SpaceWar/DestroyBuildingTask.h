// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskBase.h"
#include "DestroyBuildingTask.generated.h"

class AEnemyHouse;
/**
 * 
 */
UCLASS()
class SPACEWAR_API ADestroyBuildingTask : public ATaskBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	TArray<AEnemyHouse*> EnemyBuildings;

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnBuildingDestroyed(AEnemyHouse* Building );
};
