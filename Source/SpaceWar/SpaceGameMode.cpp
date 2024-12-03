// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameMode.h"

#include "BossBase.h"
#include "CargoCarrier.h"
#include "CarrierSpawnPoint.h"
#include "SpaceGameInstance.h"
#include "TaskBase.h"
#include "WorldDifficulty.h"
#include "Kismet/GameplayStatics.h"

int ASpaceGameMode::GetCurrentUpgrade()
{
	return GameInstance->GetCurrentUpgrade();
}

USpaceGameInstance* ASpaceGameMode::GetGameInstance()
{
	return GameInstance;
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
	GameInstance = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->StartTimer();

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

	actors.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACarrierSpawnPoint::StaticClass(), actors);
	for (auto Actor : actors)
	{
		CarrierSpawnPoints.Add(Cast<ACarrierSpawnPoint>(Actor));
	}

	GetWorld()->GetTimerManager().SetTimer(CarrierSpawnTimer, this, &ASpaceGameMode::SpawnCarrier, TimeToSpawnCarrier,
	                                       true);

	Super::BeginPlay();
}

void ASpaceGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Type::Quit ||
		EndPlayReason == EEndPlayReason::Type::LevelTransition ||
		EndPlayReason == EEndPlayReason::Type::EndPlayInEditor)
	{
		GameInstance->StopTimer();
	}
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

void ASpaceGameMode::SpawnCarrier()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	int randomCarrier = FMath::RandRange(0, Carriers.Num() - 1);
	int randomPoint = FMath::RandRange(0, CarrierSpawnPoints.Num() - 1);

	ACargoCarrier* cargo = GetWorld()->SpawnActor<ACargoCarrier>(Carriers[randomCarrier],
	                                                             CarrierSpawnPoints[randomPoint]->GetActorLocation(),
	                                                             CarrierSpawnPoints[randomPoint]->GetActorRotation(),
	                                                             SpawnInfo);

	UE_LOG(LogTemp, Display, TEXT("Spawned"));
}
