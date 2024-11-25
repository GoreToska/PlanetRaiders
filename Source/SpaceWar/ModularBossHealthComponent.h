// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "ModularBossHealthComponent.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWAR_API UModularBossHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

public:
	void ModuleDestroyed(float Damage);
};
