// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "GameFramework/Actor.h"
#include "SpaceEngine.generated.h"

class UHealthComponent;

UCLASS()
class SPACEWAR_API ASpaceEngine : public AActor, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceEngine();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDead);

	UPROPERTY(BlueprintAssignable)
	FDead OnDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath() override;
};
