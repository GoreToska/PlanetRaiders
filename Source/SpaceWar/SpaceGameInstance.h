// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataAsset.h"
#include "Engine/GameInstance.h"
#include "SpaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPACEWAR_API USpaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgrade, int, value);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimer);

	UPROPERTY(BlueprintAssignable)
	FOnUpgrade OnUpgraded;
	UPROPERTY(BlueprintAssignable)
	FOnTimer OnTimerChanged;

	UPROPERTY(BlueprintReadOnly)
	int CurrentTime;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetSeconds();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetMinutes();
	void StartTimer();
	void StopTimer();
	UFUNCTION(BlueprintCallable)
	void NewGame();

	UFUNCTION(BlueprintCallable)
	int GetCurrentUpgrade();

	UPROPERTY()
	FTimerHandle WorldTimer;
	void OnTimerTick();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeToUpgrade = 60;

	UPROPERTY()
	TArray<UItemDataAsset*> PlayerItems;
	
protected:
	int CurrentUpgrade;
};
