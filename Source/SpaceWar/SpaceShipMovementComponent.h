// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpaceShipMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API USpaceShipMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpaceShipMovementComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	void ChangeSpeed(float Value);
	void Turn(FVector2D Value);
	void ChangeRotation(float Value);
	UPROPERTY()
	AActor* OwningActor;

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
	float InterpolationSpeed = 2;
	UPROPERTY(EditAnywhere)
	float SpeedChangingMultiplier = 400;
	bool bIsAiming = false;
	float CurrentSpeed;
	FRotator CurrentRotateRotation;
	FRotator CurrentTurnRotation;
	FVector CurrentTurnInput;
	float CurrentRotateInput;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PerformTurn(float DeltaTime, bool IsAiming);
	void PerformMovementForward(float DeltaTime);
	void PerformRotation(float DeltaTime);
	void ClampSpeed();

	
};
