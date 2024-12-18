// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "PlayerShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::GetDamage(float Damage)
{
	if (CurrentHP <= 0)
		return;

	Damage = Damage > 0 ? Damage : -Damage;
	CurrentHP -= Damage;
	OnSetHealth.Broadcast(CurrentHP);
	OnGetDamage.Broadcast(Damage);

	if (CurrentHP <= 0)
	{
		Death();
	}
}

void UHealthComponent::GetHeal(float Heal)
{
	Heal = Heal > 0 ? Heal : -Heal;
	CurrentHP += Heal;
	CurrentHP = CurrentHP > MaxHP ? MaxHP : CurrentHP;
	OnSetHealth.Broadcast(CurrentHP);
}

void UHealthComponent::Death()
{
	// TODO:Sound
	DestroyEffect();

	if (DeathSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetOwner()->GetActorLocation());
	}

	CurrentHP = 0;
	OnSetHealth.Broadcast(CurrentHP);
	Cast<IDestructible>(GetOwner())->HandleDeath();
}

void UHealthComponent::DestroyEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticles, GetOwner()->GetActorLocation(),
	                                         GetOwner()->GetActorRotation(), DeathParticleScale);
}

void UHealthComponent::SetNewMaxHealth(float health)
{
	float NewCurrentHPModifier = CurrentHP / MaxHP;
	MaxHP = health;
	CurrentHP = MaxHP * NewCurrentHPModifier;
	OnSetHealth.Broadcast(CurrentHP);
}

bool UHealthComponent::IsAlive()
{
	return CurrentHP > 0;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CurrentHP = MaxHP;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
