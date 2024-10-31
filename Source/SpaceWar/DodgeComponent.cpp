// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeComponent.h"

#include "SpaceShipBase.h"

// Sets default values for this component's properties
UDodgeComponent::UDodgeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DodgeCurve)
	{
		DodgeCurve->GetTimeRange(MinDodgeTime, MaxDodgeTime);
		UE_LOG(LogTemp, Warning, TEXT("There is curve on dodge component!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no curve on dodge component!"));
	}

	if (RotationCurve)
	{
		RotationCurve->GetTimeRange(MinRotationTime, MaxRotationTime);
	}

	OwningActor = Cast<ASpaceShipBase>(GetOwner());
	bIsDodging = false;
	DodgeTime = 0;
	PrevDodgeTime = 0;
}


// Called every frame
void UDodgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsDodging)
	{
		if (DodgeTime >= MaxDodgeTime)
		{
			bIsDodging = false;
			DodgeTime = 0;
			PrevDodgeTime = 0;
		}

		float CurveValue = DodgeCurve->GetFloatValue(DodgeTime);
		float DeltaCurve = CurveValue - PrevDodgeTime;
		PrevDodgeTime = CurveValue;
		OwningActor->AddActorLocalOffset(DodgeSideModifier * DodgeSpeed * DeltaTime * DeltaCurve);
		DodgeTime += DeltaTime;
	}
}

void UDodgeComponent::PerformDodge(const FVector& InputVector)
{
	if (DodgeCurve == nullptr) return;
	if (bIsDodging) return;

	DodgeSideModifier = InputVector;
	DodgeSideModifier.Normalize();
	bIsDodging = true;
}
