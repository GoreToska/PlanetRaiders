// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "ProjectileBase.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGun::FireShot(float DamageModifier)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle))
		return;

	UE_LOG(LogTemp, Display, TEXT("Shot!"));
	if (SavedDamageModifier != DamageModifier)
	{
		SavedDamageModifier = DamageModifier;
	}

	GetWorld()->GetTimerManager().SetTimer(ShootingTimerHandle, this, &AGun::PerformShot,
	                                       60 / FireSpeedPerSec,
	                                       false);
}

void AGun::PerformShot()
{
	FVector Location = GetActorLocation();
	FRotator Rotation = GetActorRotation();
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UE_LOG(LogTemp, Display, TEXT("Shot!"));

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		Projectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(SavedDamageModifier);
	}
}

void AGun::Equip()
{
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}
