// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"

#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void AHomingProjectile::SetProjectileHomingTarget(APlayerShip* playerShip)
{
	PlayerShip = playerShip;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingTargetComponent = PlayerShip->GetComponentByClass<UMeshComponent>();
	PlayerShip->OnUsedFlare.AddDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
}

void AHomingProjectile::ClearProjectileHomingTarget()
{
	ProjectileMovementComponent->bIsHomingProjectile = false;
}

void AHomingProjectile::StartProjectileTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &AHomingProjectile::DestroyProjectile, 1, false,
	                                       TimeToLive);
}

void AHomingProjectile::DestroyProjectile()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyParticles, GetActorLocation());
	PlayerShip->OnUsedFlare.RemoveDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	Destroy();
}

void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();
}
