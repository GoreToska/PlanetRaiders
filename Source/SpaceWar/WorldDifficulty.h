// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldDifficulty.generated.h"

UCLASS()
class SPACEWAR_API AWorldDifficulty : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldDifficulty();

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

	UFUNCTION(BlueprintCallable)
	int GetCurrentUpgrade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FTimerHandle WorldTimer;

	void OnTimerTick();

	UPROPERTY(EditAnywhere)
	int TimeToUpgrade = 60;

	int CurrentUpgrade;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
