// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Indicator.generated.h"

UCLASS()
class SPACEWAR_API AIndicator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AIndicator();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVisibilityChanged, bool, value);

	UPROPERTY(BlueprintAssignable)
	FVisibilityChanged OnVisibilityChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetVisibility(bool value);
};
