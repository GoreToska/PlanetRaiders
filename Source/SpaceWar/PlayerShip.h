// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "SpaceShipBase.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

class UInputMappingContext;
class UInputAction;
class UPlayerInventory;
class UPlayerStats;
class IStatsContainerRead;
class UCameraShake;
class AProjectileBase;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
struct FInputActionValue;

UCLASS()
class SPACEWAR_API APlayerShip : public ASpaceShipBase, public IDestructible
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerShip();

	UFUNCTION()
	void UpdateStats();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

	UPROPERTY(BlueprintAssignable)
	FOnDead OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY()
	UPlayerInventory* PlayerInventory;
	UPROPERTY(EditAnywhere)
	USoundBase* AimSound;
	UPROPERTY(EditAnywhere)
	USoundBase* FlareSound;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere)
	UInputAction* ChangeSpeedAction;
	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;
	UPROPERTY(EditAnywhere)
	UInputAction* RotateAction;
	UPROPERTY(EditAnywhere)
	UInputAction* ShotAction;
	UPROPERTY(EditAnywhere)
	UInputAction* AimAction;
	UPROPERTY(EditAnywhere)
	UInputAction* FlareAction;
	UPROPERTY(EditAnywhere)
	UInputAction* DodgeAction;
	UPROPERTY(EditAnywhere)
	UInputAction* FirstWeaponAction;
	UPROPERTY(EditAnywhere)
	UInputAction* SecondWeaponAction;

	void ChangeSpeed(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void ChangeRotation(const FInputActionValue& Value);
	void PerformShooting(const FInputActionValue& Value);
	void SwitchAim(const FInputActionValue& Value);
	void UseFlare(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void FirstWeapon(const FInputActionValue& Value);
	void SecondWeapon(const FInputActionValue& Value);

	void ChangeCameraFOV(float DeltaTime);
	void OnTimerSet();

	UPROPERTY(EditAnywhere)
	float StandardFOV = 90;
	UPROPERTY(EditAnywhere)
	float AimFOV = 40;
	UPROPERTY(EditAnywhere)
	float AimInterpolation = 10.f;
	UPROPERTY(EditAnywhere)
	float AimDistance = 20000;
	bool BIsAiming = false;

	float CurrentCameraFOV = StandardFOV;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> LowDamageCameraShake;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> HighDamageCameraShake;
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;
	virtual void OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	                       FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	void PerformDamageCameraShake(float Damage);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void HandleDeath() override;
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable)
	FVector2D GetPlayerAimDirection01();
	UFUNCTION(BlueprintCallable)
	FVector2D GetPlayerAimDirection02();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUsedFlare);

	UPROPERTY(BlueprintAssignable)
	FUsedFlare OnUsedFlare;

private:
	void ClampCurrentSpeed();
};
