// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShipMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEWAR_API USpaceShipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceShipMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1500.f;
	UPROPERTY(EditAnywhere)
	float MinSpeed = 600.f;
	UPROPERTY(EditAnywhere)
	float RotationPower = 5.f;
	UPROPERTY(EditAnywhere)
	float TurnSpeed = 1.5f;
	UPROPERTY(EditAnywhere)
	float AimingTurnSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
	float InterpolationSpeed = 10;
	UPROPERTY(EditAnywhere)
	float SpeedChangingMultiplier = 400;
};
