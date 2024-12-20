// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingProjectile.h"

#include "PlayerShip.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AHomingProjectile::SetProjectileHomingTarget(APlayerShip* playerShip)
{
	if (!playerShip)
		return;

	PlayerShip = playerShip;
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingTargetComponent = PlayerShip->GetRootComponent();

	PlayerShip->OnUsedFlare.AddDynamic(this, &AHomingProjectile::ClearProjectileHomingTarget);
	PlayerShip->AddHomingRocket(this);
	GetWorld()->GetTimerManager().SetTimer(IsPlayerInFrontTimer,
	                                       FTimerDelegate::CreateLambda([this]
	                                       {
		                                       if (FVector::DotProduct(GetActorForwardVector(),
		                                                               (GetActorLocation() - PlayerShip->
			                                                               GetActorLocation()).GetSafeNormal()) > 0)
		                                       {
			                                       ClearProjectileHomingTarget();
		                                       }
	                                       }), 0.25, true, 1);
}

void AHomingProjectile::ClearProjectileHomingTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("Clear target"));
	ProjectileMovementComponent->bIsHomingProjectile = false;
	PlayerShip->RemoveHomingRocket(this);
	GetWorld()->GetTimerManager().ClearTimer(IsPlayerInFrontTimer);
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

	Super::HandleHit();
}

void AHomingProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
