// Fill out your copyright notice in the Description page of Project Settings.


#include "GunSceneComponent.h"

#include "ProjectileBase.h"
#include "PlayerStats.h"

// Sets default values for this component's properties
UGunSceneComponent::UGunSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UGunSceneComponent::FireShot()
{
	FVector Location = GetComponentLocation();
	FRotator Rotation = GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UE_LOG(LogTemp, Display, TEXT("Shot!"));

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		Projectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(PlayerStats->DamageModifier);
	}
}

void UGunSceneComponent::PerformShot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle))
		return;

	UE_LOG(LogTemp, Display, TEXT("Shot!"));
	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UGunSceneComponent::FireShot,
	                                       60 / FireSpeedPerSec,
	                                       false);
}

void UGunSceneComponent::Equip()
{
}


// Called when the game starts
void UGunSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UGunSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
