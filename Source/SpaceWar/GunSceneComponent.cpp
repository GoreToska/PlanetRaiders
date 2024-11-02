// Fill out your copyright notice in the Description page of Project Settings.


#include "GunSceneComponent.h"

#include "ProjectileBase.h"
#include "PlayerStats.h"

// Sets default values for this component's properties
UGunSceneComponent::UGunSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UGunSceneComponent::FireShot()
{
	FVector Location = GetComponentLocation();
	FRotator Rotation = GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		Projectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(PlayerStats->DamageModifier);
	}
}

void UGunSceneComponent::PerformShot()
{
	bool IsCooldown = GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle);

	if (CurrentAmmo <= 0 || !IsCooldown)
	{
		GetWorld()->GetTimerManager()
		          .SetTimer(ShootingTimerHandle,
		                    this,
		                    &UGunSceneComponent::FireShot,
		                    60 / FireSpeedPerSec,
		                    false);
	}

	bool IsLoading = GetWorld()->GetTimerManager().IsTimerActive(LoadingTimerHandle);
	if (!IsLoading)
	{
		GetWorld()->GetTimerManager()
		          .SetTimer(LoadingTimerHandle,
		                    this,
		                    &UGunSceneComponent::LoadAmmo,
		                    TimeToLoadAmmo,
		                    true);
	}
}

void UGunSceneComponent::Equip()
{
	OnEquipped.Broadcast();
}

void UGunSceneComponent::LoadAmmo()
{
	if (CurrentAmmo < MaxAmmo)
	{
		++CurrentAmmo;
		OnBulletCountChanged.Broadcast(CurrentAmmo);
		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentAmmo);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);
	}
}

void UGunSceneComponent::SpendAmmo()
{
	--CurrentAmmo;
	OnBulletCountChanged.Broadcast(CurrentAmmo);
}


// Called when the game starts
void UGunSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerStats = GetOwner()->GetComponentByClass<UPlayerStats>();
	CurrentAmmo = MaxAmmo;
}
