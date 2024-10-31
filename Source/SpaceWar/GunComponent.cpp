// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"

#include "PlayerStats.h"
#include "ProjectileBase.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	FireSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Socket"));
}


// Called when the game starts
void UGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//FireSocket = FireSocketObject.GetComponent();
}

void UGunComponent::FireShot()
{
	FVector Location = FireSocket->GetComponentLocation();
	FRotator Rotation = FireSocket->GetComponentRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		Projectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(PlayerStats->DamageModifier);
	}
}

void UGunComponent::PerformShot()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle))
		return;

	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &UGunComponent::FireShot, 60 / FireSpeedPerSec,
	                                       false);
	//FireShot();
}

void UGunComponent::Equip()
{
	OnEquipped.Broadcast();
}
