// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "GameFramework/Pawn.h"
#include "BossBase.generated.h"

class UModularBossHealthComponent;
class ASpaceEngine;

UCLASS()
class SPACEWAR_API ABossBase : public APawn, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABossBase();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UModularBossHealthComponent* HealthComponent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBossDestroyed);

	UPROPERTY(BlueprintAssignable)
	FBossDestroyed OnDestroy;

	virtual void HandleDeath() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ASpaceEngine*> Engines;
	int EnginesCount;
	UFUNCTION()
	void OnEngineDead();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};