// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceGameMode.generated.h"

class ACargoCarrier;
class ACarrierSpawnPoint;
class USpaceGameInstance;
class ATaskBase;
class ABossBase;
class AWorldDifficulty;
/**
 * 
 */
UCLASS()
class SPACEWAR_API ASpaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	int GetCurrentUpgrade();
	UFUNCTION(BlueprintCallable)
	USpaceGameInstance* GetGameInstance();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABossBase> LevelBoss;

	UFUNCTION(BlueprintCallable)
	ABossBase* SpawnBoss(FTransform Transform);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBossSpawned);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTasksCompleted);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTaskCompleted, ATaskBase*, value);

	UPROPERTY(BlueprintAssignable)
	FBossSpawned OnBossSpawned;
	UPROPERTY(BlueprintAssignable)
	FBossSpawned OnAllTasksCompleted;
	UPROPERTY(BlueprintAssignable)
	FTaskCompleted OnTaskComplete;

	UPROPERTY(BlueprintReadOnly)
	TArray<ATaskBase*> Tasks;

	UPROPERTY()
	TArray<ACarrierSpawnPoint*> CarrierSpawnPoints;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ACargoCarrier>> Carriers;

	UPROPERTY(BlueprintReadOnly)
	USpaceGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	float TimeToSpawnCarrier = 40;

	FTimerHandle CarrierSpawnTimer;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnTaskCompleted(ATaskBase* Task);

	void SpawnCarrier();
};
