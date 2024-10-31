// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingTurret.h"

#include "HomingProjectile.h"
#include "PlayerShip.h"
#include "ProjectileBase.h"

void AHomingTurret::SetupProjectile(FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AHomingProjectile* HomingProjectile = GetWorld()->
		SpawnActor<AHomingProjectile>(Projectile, Location, Rotation, SpawnInfo);
	
	if (!this || !HomingProjectile)
		return;

	HomingProjectile->SetOwner(this);
	HomingProjectile->SetProjectileHomingTarget(PlayerShip);
	HomingProjectile->StartProjectileTimer();
}
