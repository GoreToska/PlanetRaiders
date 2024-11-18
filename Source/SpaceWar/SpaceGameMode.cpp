// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameMode.h"

#include "WorldDifficulty.h"

AWorldDifficulty* ASpaceGameMode::GetWorldDifficulty()
{
	return WorldDifficulty;
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
