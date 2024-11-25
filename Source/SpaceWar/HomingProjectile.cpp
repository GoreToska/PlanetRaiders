// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"

#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AHomingProjectile::SetProjectileHomingTarget(APlayerShip* playerShip)
{
	PlayerShip = playerShip;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingTargetComponent = PlayerShip->GetRootComponent();

	PlayerShip->OnUsedFlare.AddDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	PlayerShip->AddHomingRocket(this);
}

void AHomingProjectile::ClearProjectileHomingTarget()
{
	ProjectileMovementComponent->bIsHomingProjectile = false;
	PlayerShip->RemoveHomingRocket(this);
}

void AHomingProjectile::DestroyProjectile()
{
	PlayerShip->OnUsedFlare.RemoveDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	PlayerShip->RemoveHomingRocket(this);
	Super::DestroyProjectile();
}

void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AHomingProjectile::HandleHit()
{
	if (this)
		PlayerShip->RemoveHomingRocket(this);

	UE_LOG(LogTemp, Display, TEXT("this null - %hhd, player null - %hhd"), this == nullptr, PlayerShip == nullptr);
	Super::HandleHit();
}
