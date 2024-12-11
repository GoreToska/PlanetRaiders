// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SpawnedAudioLoop = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioLoop"));
	BoxComponent->SetupAttachment(SceneComponent);
	BoxComponent->SetCollisionProfileName(TEXT("BlockAllDinamics"));
	SetRootComponent(BoxComponent);

	//ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	//ParticleSystemComponent->SetupAttachment(BoxComponent);

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
	DamageModifier = modifier;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//BoxComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnBeginOverlap);

	if (LoopSound)
	{
		SpawnedAudioLoop->AttachToComponent(GetRootComponent(),
		                                    FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	StartProjectileTimer();
}

void AProjectileBase::CreateSoundAndFX()
{
	if (HitEffect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitEffect, GetActorLocation());

	if (HitSound)
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, GetActorLocation());
}

void AProjectileBase::GetSplashDamage()
{
	TArray<AActor*> Actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	ActorsToIgnore.Add(HitActor);
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		SplashRadius,
		ObjectTypes,
		AActor::StaticClass(),
		ActorsToIgnore,
		Actors);

	if (Actors.Num() <= 0)
	{
		return;
	}

	for (AActor* a : Actors)
	{
		UHealthComponent* health = a->GetComponentByClass<UHealthComponent>();
		if (!health)
			continue;

		health->GetDamage(SplashDamage * DamageModifier);
	}
}

void AProjectileBase::HandleHit()
{
	CreateSoundAndFX();

	if (SplashRadius > 0)
		GetSplashDamage();


	if (SpawnedAudioLoop)
		SpawnedAudioLoop->Stop();

	Destroy();
}

void AProjectileBase::DestroyProjectile()
{
	CreateSoundAndFX();
	GetSplashDamage();
	Destroy();
}

void AProjectileBase::StartProjectileTimer()
{
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &AProjectileBase::DestroyProjectile, 1, false,
	                                       TimeToLive);
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
		if (GetOwner() && HealthComponent->Team != GetOwner()->GetComponentByClass<UHealthComponent>()->Team)
		{
			HealthComponent->GetDamage(Damage * DamageModifier);
			HitActor = OtherActor;
		}
	}

	HandleHit();
}
