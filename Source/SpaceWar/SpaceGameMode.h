// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceGameMode.generated.h"

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
	UFUNCTION(BlueprintCallable)
	AWorldDifficulty* GetWorldDifficulty();

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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWorldDifficulty> WorldDifficultyObject;
	UPROPERTY()
	AWorldDifficulty* WorldDifficulty;

	UFUNCTION()
	void OnTaskCompleted(ATaskBase* Task);
};
