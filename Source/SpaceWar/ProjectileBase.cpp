// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "HealthComponent.h"
#include "Components/AudioComponent.h"
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

	if (LoopSound)
		SpawnedAudioLoop = UGameplayStatics::SpawnSoundAttached(LoopSound, GetRootComponent());
}

void AProjectileBase::CreateSoundAndFX()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation(), FRotator::ZeroRotator,
	                                         HitEffectScale);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, GetActorLocation());
}

void AProjectileBase::GetSplashDamage()
{
	TArray<AActor*> Actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	DrawDebugSphere(GetWorld(), GetActorLocation(), SplashRadius, 32, FColor::Red, false, 10);
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetActorLocation(),
		SplashRadius,
		ObjectTypes,
		AActor::StaticClass(),
		ActorsToIgnore,
		Actors);
	
	UE_LOG(LogTemp, Warning, TEXT("%d"), Actors.Num());

	if (Actors.Num() <= 0)
	{
		return;
	}

	for (AActor* a : Actors)
	{
		UHealthComponent* health = a->GetComponentByClass<UHealthComponent>();
		if (!health)
			continue;

		health->GetDamage(SplashDamage);
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

	HandleHit();
}
