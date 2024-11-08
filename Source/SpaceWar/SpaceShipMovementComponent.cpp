// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipMovementComponent.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpaceShipMovementComponent::USpaceShipMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USpaceShipMovementComponent::PerformTurn(float DeltaTime, bool IsAiming)
{
	FRotator TurnRotation = CurrentTurnInput.Rotation();
	CurrentTurnRotation = FMath::RInterpTo(CurrentTurnRotation, TurnRotation,
	                                       DeltaTime, InterpolationSpeed);
	if (IsAiming)
	{
		OwningActor->AddActorLocalRotation(CurrentTurnRotation * DeltaTime * AimingTurnSpeed);
	}
	else
	{
		OwningActor->AddActorLocalRotation(CurrentTurnRotation * DeltaTime * TurnSpeed);
	}
}

void USpaceShipMovementComponent::PerformMovementForward(float DeltaTime)
{
	OwningActor->AddActorWorldOffset(
		OwningActor->GetActorForwardVector() *
		CurrentSpeed * DeltaTime, true);
}

void USpaceShipMovementComponent::PerformRotation(float DeltaTime)
{
	FRotator TurnRotation = FRotator(0, 0, CurrentRotateRotation.Pitch + CurrentRotateInput);
	CurrentRotateRotation = FMath::RInterpTo(CurrentRotateRotation, TurnRotation,
	                                         DeltaTime, RotationPower);

	OwningActor->AddActorLocalRotation(CurrentRotateRotation * DeltaTime);
}

void USpaceShipMovementComponent::ClampSpeed()
{
	if (CurrentSpeed <= MinSpeed)
		CurrentSpeed = MinSpeed;

	if (CurrentSpeed >= MaxSpeed)
		CurrentSpeed = MaxSpeed;
}

// Called when the game starts
void USpaceShipMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningActor = GetOwner();
	CurrentSpeed = MinSpeed;
	EngineAudio = UGameplayStatics::SpawnSoundAttached(EngineSound, GetOwner()->GetRootComponent());
	// ...
}


// Called every frame
void USpaceShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	PerformRotation(DeltaTime);
	PerformMovementForward(DeltaTime);
	PerformTurn(DeltaTime, bIsAiming);

	float NormalizedSpeed = (CurrentSpeed - MinSpeed) / (MaxSpeed - MinSpeed);
	EngineAudio->SetFloatParameter("Speed", NormalizedSpeed);
}

void USpaceShipMovementComponent::ChangeSpeed(float Value)
{
	CurrentSpeed += Value * SpeedChangingMultiplier * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	ClampSpeed();
}

void USpaceShipMovementComponent::Turn(FVector2D Value)
{
	FVector2d TurnVector = Value;
	CurrentTurnInput = FVector(0, TurnVector.X, -TurnVector.Y);
}

void USpaceShipMovementComponent::ChangeRotation(float Value)
{
	CurrentRotateInput = Value * 100;
}
