// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere)
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP = 100;
	virtual void GetDamage(float Damage);
	virtual void GetHeal(float Heal);
	virtual void Death();
	virtual void DestroyEffect();
	void SetNewMaxHealth(float health);
	bool IsAlive();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetHealthDelegate, float, NewHealth);

	UPROPERTY(BlueprintAssignable)
	FSetHealthDelegate OnSetHealth;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGotDamageDelegate, float, Damage);

	UPROPERTY(BlueprintAssignable)
	FGotDamageDelegate OnGetDamage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UParticleSystem* DeathParticles;
	UPROPERTY(EditAnywhere)
	FVector DeathParticleScale = FVector(10, 10, 10);
	UPROPERTY(EditAnywhere)
	USceneComponent* DeathEffectPosition;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
