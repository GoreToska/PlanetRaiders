// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"

#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AHomingProjectile::SetProjectileHomingTarget(APlayerShip* playerShip)
{
	PlayerShip = playerShip;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingTargetComponent = PlayerShip->GetComponentByClass<UMeshComponent>();

	PlayerShip->OnUsedFlare.AddDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	PlayerShip->AddHomingRocket(this);
}

void AHomingProjectile::ClearProjectileHomingTarget()
{
	ProjectileMovementComponent->bIsHomingProjectile = false;
	PlayerShip->RemoveHomingRocket(this);
}

void AHomingProjectile::StartProjectileTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &AHomingProjectile::DestroyProjectile, 1, false,
	                                       TimeToLive);
}

void AHomingProjectile::DestroyProjectile()
{
	CreateSoundAndFX();
	PlayerShip->OnUsedFlare.RemoveDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	PlayerShip->RemoveHomingRocket(this);
	Destroy();
}

void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AHomingProjectile::HandleHit()
{
	Super::HandleHit();
	
	PlayerShip->RemoveHomingRocket(this);
}
