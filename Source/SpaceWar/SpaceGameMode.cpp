// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameMode.h"

#include "BossBase.h"
#include "TaskBase.h"
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

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaskBase::StaticClass(), actors);

	for (auto Actor : actors)
	{
		ATaskBase* task = Cast<ATaskBase>(Actor);
		if (task)
		{
			Tasks.Add(task);
			task->OnCompleted.AddDynamic(this, &ASpaceGameMode::OnTaskCompleted);
		}
	}

	Super::BeginPlay();
}

void ASpaceGameMode::OnTaskCompleted(ATaskBase* Task)
{
	OnTaskComplete.Broadcast(Task);
	Tasks.Remove(Task);

	if (Tasks.Num() <= 0)
	{
		OnAllTasksCompleted.Broadcast();
	}
}
