// Fill out your copyright notice in the Description page of Project Settings.


#include "GunSceneComponent.h"

#include "ProjectileBase.h"
#include "PlayerStats.h"
#include "Kismet/GameplayStatics.h"

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

	Rotation.Pitch += FMath::RandRange(-Spread.X, Spread.X);
	Rotation.Yaw += FMath::RandRange(-Spread.Y, Spread.Y);

	if (AProjectileBase* ProjectileBase = GetWorld()->SpawnActor<AProjectileBase>(
		Projectile, Location, Rotation, SpawnInfo); this && ProjectileBase)
	{
		ProjectileBase->SetOwner(GetOwner());
		ProjectileBase->SetProjectileDamageModifier(PlayerStats->DamageModifier);
		PlayShotSound(ProjectileBase->GetRootComponent());
	}
}

void UGunSceneComponent::PerformShot()
{
	bool IsCooldown = GetWorld()->GetTimerManager().IsTimerActive(ShootingTimerHandle);

	if (IsCooldown)
		return;

	if (CurrentAmmo <= 0)
	{
		//UGameplayStatics::SpawnSound2D(this, EmptySound);
		return;
	}

	FireShot();
	SpendAmmo();

	GetWorld()->GetTimerManager()
	          .SetTimer(ShootingTimerHandle,
	                    this,
	                    &UGunSceneComponent::OnShotFired,
	                    60 / FireSpeedPerSec,
	                    false);


	bool IsLoading = GetWorld()->GetTimerManager().IsTimerActive(LoadingTimerHandle);
	if (IsLoading)
		return;

	GetWorld()->GetTimerManager()
	          .SetTimer(LoadingTimerHandle,
	                    this,
	                    &UGunSceneComponent::LoadAmmo,
	                    TimeToLoadAmmo,
	                    true);
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

void UGunSceneComponent::PlayShotSound(USceneComponent* ActorRoot)
{
	UGameplayStatics::SpawnSoundAttached(ShotSound, ActorRoot);
}

FVector2D UGunSceneComponent::GetFirstCrosshairPosition() const
{
	FVector2D ScreenLocation;
	FVector CrosshairPosition = GetComponentLocation() + GetForwardVector() * Distance * 10;
	UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(
		CrosshairPosition, ScreenLocation);

	return ScreenLocation;
}

FVector2D UGunSceneComponent::GetSecondCrosshairPosition() const
{
	FVector2D ScreenLocation;
	FVector CrosshairPosition = GetComponentLocation() + GetForwardVector() * Distance;
	UGameplayStatics::GetPlayerController(this, 0)->ProjectWorldLocationToScreen(
		CrosshairPosition, ScreenLocation);

	return ScreenLocation;
}

// Called when the game starts
void UGunSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerStats = GetOwner()->GetComponentByClass<UPlayerStats>();
	CurrentAmmo = MaxAmmo;
}

void UGunSceneComponent::OnShotFired()
{
}
