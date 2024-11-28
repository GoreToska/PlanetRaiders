// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBase.h"

#include "ModularBossHealthComponent.h"
#include "SpaceEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

void ABossBase::RotateTowardsPlayer()
{
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!player)
		return;

	FVector LookAtVector = player->GetActorLocation();
	LookAtVector.Z = RootComponent->GetComponentLocation().Z;
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(RootComponent->GetComponentLocation(),
	                                                                 LookAtVector);
	RootComponent->SetWorldRotation(LookAtRotation);
}

void ABossBase::TeleportToPlayer()
{
	float XCoordinate = FMath::RandRange(MinTeleportRadius.X, MaxTeleportRadius.X) * GetRandomModifier();
	float YCoordinate = FMath::RandRange(MinTeleportRadius.Y, MaxTeleportRadius.Y) * GetRandomModifier();
	float ZCoordinate = FMath::RandRange(MinTeleportRadius.Z, MaxTeleportRadius.Z);

	FVector PlayerPosition = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	FVector NewPosittion = FVector(
		PlayerPosition.X + XCoordinate,
		PlayerPosition.Y + YCoordinate,
		PlayerPosition.Z + ZCoordinate);

	SetActorLocation(NewPosittion);
	bIsRotating = true;
	GetWorldTimerManager().SetTimer(RotationTimer,
	                                FTimerDelegate::CreateLambda([this]
	                                {
		                                this->bIsRotating = false;
	                                }),
	                                0.1, false, RotationTime);
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

	GetWorldTimerManager().SetTimer(TeleportTimer,
	                                this,
	                                &ABossBase::TeleportToPlayer,
	                                TimeToTeleport,
	                                true,
	                                FirstTeleportDelay);
}

void ABossBase::OnEngineDead()
{
	HealthComponent->ModuleDestroyed(HealthComponent->MaxHP / EnginesCount);
}

int ABossBase::GetRandomModifier()
{
	int random = FMath::RandRange(0, 100);
	return random >= 50 ? -1 : 1;
}

// Called every frame
void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRotating)
		RotateTowardsPlayer();
}

// Called to bind functionality to input
void ABossBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
