// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskBase.generated.h"

class AIndicator;

UCLASS()
class SPACEWAR_API ATaskBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATaskBase();

	void CompleteTask();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTaskCompleted, ATaskBase*, value);

	UPROPERTY(BlueprintAssignable)
	FTaskCompleted OnCompleted;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AIndicator> Indicator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AIndicator* TaskIndicator;
	UPROPERTY(EditAnywhere)
	int Distance = 2000;

	bool IsObjectsVisible = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
