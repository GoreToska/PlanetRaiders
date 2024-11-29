// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class SPACEWAR_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBase();

	void SetProjectileStartSpeed(float Speed);

	float GetProjectileSpeed();
	void SetProjectileDamageModifier(float modifier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreateSoundAndFX();
	void GetSplashDamage();
	virtual void HandleHit();
	virtual void DestroyProjectile();
	virtual void StartProjectileTimer();

	UPROPERTY()
	FTimerHandle DestructionTimer;
	UPROPERTY(EditAnywhere)
	float TimeToLive = 5.f;
	//UPROPERTY(EditAnywhere)
	//UParticleSystem* DestroyParticles;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	//UPROPERTY(EditAnywhere)
	//UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditAnywhere)
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere)
	FVector HitEffectScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere)
	USoundBase* LoopSound;
	UPROPERTY(EditAnywhere)
	float SplashRadius = 0;
	UPROPERTY()
	UAudioComponent* SpawnedAudioLoop;
	UPROPERTY()
	AActor* HitActor = nullptr;
	UPROPERTY(EditAnywhere)
	float Damage = 10;
	UPROPERTY(EditAnywhere)
	float SplashDamage = 10;
	float DamageModifier = 1;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
