// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxComponent->SetupAttachment(SceneComponent);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDinamics"));
	SetRootComponent(BoxComponent);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	ParticleSystemComponent->SetupAttachment(BoxComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

void AProjectileBase::SetProjectileStartSpeed(float Speed)
{
	ProjectileMovementComponent->InitialSpeed += Speed;
	ProjectileMovementComponent->MaxSpeed += Speed;
}

float AProjectileBase::GetProjectileSpeed()
{
	return ProjectileMovementComponent->InitialSpeed;
}

void AProjectileBase::SetProjectileDamageModifier(float modifier)
{
	Damage *= modifier;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//BoxComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnBeginOverlap);
}

void AProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	if (Cast<AProjectileBase>(OtherActor))
		return;

	if (UHealthComponent* HealthComponent = OtherActor->GetComponentByClass<UHealthComponent>())
	{
		HealthComponent->GetDamage(Damage);
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), FRotator::ZeroRotator,
	                                         HitEffectScale);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	Destroy();
}
