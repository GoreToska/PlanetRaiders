// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyBuildingTask.h"

#include "EnemyHouse.h"

void ADestroyBuildingTask::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyBuildings.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy Buildings is empty!"));
	}

	for (auto Building : EnemyBuildings)
	{
		Building->OnBuildingDestroyed.AddDynamic(this, &ADestroyBuildingTask::OnBuildingDestroyed);

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* indicator = GetWorld()->SpawnActor<AActor>(Indicator, Building->GetActorLocation(),
		                                                   Building->GetActorRotation(), SpawnInfo);

		indicator->AttachToActor(Building, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void ADestroyBuildingTask::OnBuildingDestroyed(AEnemyHouse* Building)
{
	TArray<AActor*> OutActors;
	Building->GetAttachedActors(OutActors);
	for (auto OutActor : OutActors)
	{
		OutActor->Destroy();
	}
	
	EnemyBuildings.Remove(Building);

	if (EnemyBuildings.Num() > 0)
		return;

	CompleteTask();
}
