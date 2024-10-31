// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpaceShip.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemySpaceShip::AEnemySpaceShip()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Ship Movement"));
	ProjectileMovementComponent->bSweepCollision = true;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//ProjectileMovementComponent->InitialSpeed = 1000;
}

void AEnemySpaceShip::FollowTarget(AActor* Pawn)
{
	ProjectileMovementComponent->bIsHomingProjectile = true;
	ProjectileMovementComponent->HomingTargetComponent = Pawn->GetComponentByClass<UStaticMeshComponent>();
}

void AEnemySpaceShip::StopFollow()
{
	ProjectileMovementComponent->bIsHomingProjectile = false;
	ProjectileMovementComponent->HomingTargetComponent = nullptr;
}

bool AEnemySpaceShip::HasTarget()
{
	return bHasTarget;
}

void AEnemySpaceShip::BeginPlay()
{
	Super::BeginPlay();

	bHasTarget = true;
	FollowTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AEnemySpaceShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemySpaceShip::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnCollide(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);

	UE_LOG(LogTemp, Warning, TEXT("Collide!"));

	if (bHasTarget)
		FollowTarget(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
