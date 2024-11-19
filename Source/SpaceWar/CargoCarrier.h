// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "ItemDataAsset.h"
#include "GameFramework/Pawn.h"
#include "CargoCarrier.generated.h"

class UPlayerInventory;
class IPickUp;
class AStatsManager;
class UBoxComponent;
class UHealthComponent;

UCLASS()
class SPACEWAR_API ACargoCarrier : public APawn, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACargoCarrier();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UPlayerInventory* Inventory;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void HandleDeath() override;
	virtual void GetReward();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemDataAsset> CarryItem;

	UFUNCTION()
	void Upgrade(int Upgrade);

private:
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 500;
	void MoveForward(float deltaTime);

	UPROPERTY(EditAnywhere)
	float IncreaseExponent = 0.2;
	int CurrentUpgrade = 0;
};
