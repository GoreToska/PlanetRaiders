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

void AHomingProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UE_LOG(LogTemp, Warning, TEXT("%f"),
	       FVector::DotProduct(GetActorForwardVector(),(GetActorLocation() - PlayerShip->GetActorLocation()).
		       GetSafeNormal()));
}
