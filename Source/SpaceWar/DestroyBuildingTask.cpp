// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyBuildingTask.h"

#include "EnemyHouse.h"
#include "Indicator.h"
#include "Kismet/GameplayStatics.h"

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

		AIndicator* indicator = GetWorld()->SpawnActor<AIndicator>(Indicator, Building->GetActorLocation(),
		                                                           Building->GetActorRotation(), SpawnInfo);

		indicator->AttachToActor(Building, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		BuildingsAndIndicators.Add(Building, indicator);
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

	//EnemyBuildings.Remove(Building);
	BuildingsAndIndicators.Remove(Building);

	if (BuildingsAndIndicators.Num() > 0)
		return;

	CompleteTask();
}

void ADestroyBuildingTask::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (FVector::Distance(GetActorLocation(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation())
		< Distance && !IsObjectsVisible)
	{
		for (auto Element : BuildingsAndIndicators)
		{
			Element.Value->SetVisibility(true);
		}

		TaskIndicator->SetVisibility(false);
		IsObjectsVisible = true;
	}
	else if (FVector::Distance(GetActorLocation(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation())
		> Distance && IsObjectsVisible)
	{
		for (auto Element : BuildingsAndIndicators)
		{
			Element.Value->SetVisibility(false);
		}

		TaskIndicator->SetVisibility(true);
		IsObjectsVisible = false;
	}
}
