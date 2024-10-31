// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DodgeComponent.generated.h"


class ASpaceShipBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UDodgeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDodgeComponent();

	UPROPERTY(EditAnywhere)
	UCurveFloat* DodgeCurve;
	UPROPERTY(EditAnywhere)
	UCurveFloat* RotationCurve;
	UPROPERTY(EditAnywhere)
	float DodgeSpeed = 1000;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void PerformDodge(const FVector& InputVector);

private:
	UPROPERTY()
	ASpaceShipBase* OwningActor;

	FTimerHandle DodgeTimer;

	bool bIsDodging;
	FVector DodgeSideModifier;
	float DodgeTime;
	float PrevDodgeTime = 0;
	float MinDodgeTime;
	float MaxDodgeTime;
	float MinRotationTime;
	float MaxRotationTime;
};
