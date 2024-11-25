// Fill out your copyright notice in the Description page of Project Settings.


#include "ModularBossHealthComponent.h"

void UModularBossHealthComponent::ModuleDestroyed(float Damage)
{
	GetDamage(Damage);
}
