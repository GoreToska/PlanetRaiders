// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "GameFramework/Actor.h"
#include "EnemyHouse.generated.h"

class UHealthComponent;
class UBoxComponent;

UCLASS()
class SPACEWAR_API AEnemyHouse : public AActor, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyHouse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath() override;
};
