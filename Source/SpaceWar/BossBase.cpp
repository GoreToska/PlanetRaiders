// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBase.h"

#include "ModularBossHealthComponent.h"
#include "SpaceEngine.h"

// Sets default values
ABossBase::ABossBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UModularBossHealthComponent>(TEXT("Health"));
}

void ABossBase::HandleDeath()
{
	OnDestroy.Broadcast();
	Destroy();
}

// Called when the game starts or when spawned
void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors);

	for (auto ChildActor : ChildActors)
	{
		if (ASpaceEngine* CastedActor = Cast<ASpaceEngine>(ChildActor))
		{
			Engines.Add(CastedActor);
			CastedActor->OnDead.AddDynamic(this, &ABossBase::ABossBase::OnEngineDead);
		}
	}

	EnginesCount = Engines.Num();
}

void ABossBase::OnEngineDead()
{
	HealthComponent->ModuleDestroyed(HealthComponent->MaxHP / EnginesCount);
}

// Called every frame
void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABossBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
