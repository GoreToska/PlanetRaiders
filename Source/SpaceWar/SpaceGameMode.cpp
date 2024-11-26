// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameMode.h"

#include "BossBase.h"
#include "WorldDifficulty.h"
#include "Kismet/GameplayStatics.h"

AWorldDifficulty* ASpaceGameMode::GetWorldDifficulty()
{
	return WorldDifficulty;
}

ABossBase* ASpaceGameMode::SpawnBoss(FTransform Transform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ABossBase* Boss = GetWorld()->
		SpawnActor<ABossBase>(LevelBoss, Transform, SpawnInfo);

	OnBossSpawned.Broadcast();

	return Boss;
}

void ASpaceGameMode::BeginPlay()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector Location = FVector::Zero();
	FRotator Rotation = FRotator::ZeroRotator;

	WorldDifficulty = GetWorld()->
		SpawnActor<AWorldDifficulty>(WorldDifficultyObject, Location, Rotation, SpawnInfo);
	UE_LOG(LogTemp, Warning, TEXT("%hhd"), WorldDifficulty != nullptr);

	Super::BeginPlay();
}
