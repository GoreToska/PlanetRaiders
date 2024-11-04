// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Destructible.h"
#include "SpaceShipBase.h"
#include "GameFramework/Pawn.h"
#include "PlayerShip.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	UPlayerInventory* PlayerInventory;
	
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere)
	class UInputAction* AddSpeedAction;
	UPROPERTY(EditAnywhere)
	UInputAction* DecreaseSpeedAction;
	UPROPERTY(EditAnywhere)
	UInputAction* TurnAction;
	UPROPERTY(EditAnywhere)
	UInputAction* RotateRightAction;
	UPROPERTY(EditAnywhere)
	UInputAction* RotateLeftAction;
	UPROPERTY(EditAnywhere)
	UInputAction* ShotAction;
	UPROPERTY(EditAnywhere)
	UInputAction* AimAction;
	UPROPERTY(EditAnywhere)
	UInputAction* FlareAction;
	UPROPERTY(EditAnywhere)
	UInputAction* DodgeAction;

	void AddSpeed(const FInputActionValue& Value);
	void DecreaseSpeed(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void AddRightRotation(const FInputActionValue& Value);
	void AddLeftRotation(const FInputActionValue& Value);
	void PerformShooting(const FInputActionValue& Value);
	void SwitchAim(const FInputActionValue& Value);
	void UseFlare(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void SwitchGun(const FInputActionValue& Value);

	void PerformTurn(float DeltaTime);
	void PerformMovementForward(float DeltaTime);
	void PerformRotation(float DeltaTime);
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
	float BIsAiming = false;

	float CurrentCameraFOV = StandardFOV;
	FVector CurrentTurnInput;
	float CurrentRotateInput;
	FRotator CurrentTurnRotation;
	FRotator CurrentRotateRotation;

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
