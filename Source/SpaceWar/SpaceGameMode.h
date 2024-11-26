// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceGameMode.generated.h"

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

	UPROPERTY(BlueprintAssignable)
	FBossSpawned OnBossSpawned;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWorldDifficulty> WorldDifficultyObject;

	UPROPERTY()
	AWorldDifficulty* WorldDifficulty;
};
