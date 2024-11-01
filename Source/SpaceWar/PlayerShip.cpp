// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShip.h"

#include "DodgeComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gun.h"
#include "HealthComponent.h"
#include "PlayerStats.h"
#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerShip::APlayerShip()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(BoxComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);


	SpringArmComponent->bEnableCameraRotationLag;
	SpringArmComponent->CameraRotationLagSpeed = 7.f;
	SpringArmComponent->bEnableCameraLag;
	SpringArmComponent->CameraLagSpeed = 7.f;
}

// Called when the game starts or when spawned
void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

	CurrentSpeed = (MaxSpeed + MinSpeed) / 2;
	PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	HealthComponent->OnGetDamage.AddDynamic(this, &APlayerShip::PerformDamageCameraShake);

	//CurrentGunIndex = 0;
	//SetGun();
}

void APlayerShip::AddSpeed(const FInputActionValue& Value)
{
	CurrentSpeed += Value.Get<float>() * SpeedChangingMultiplier * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	ClampCurrentSpeed();
}

void APlayerShip::DecreaseSpeed(const FInputActionValue& Value)
{
	CurrentSpeed -= Value.Get<float>() * SpeedChangingMultiplier * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	ClampCurrentSpeed();
}

void APlayerShip::Turn(const FInputActionValue& Value)
{
	FVector2d TurnVector = Value.Get<FVector2d>();
	CurrentTurnInput = FVector(0, TurnVector.X, -TurnVector.Y);
}

void APlayerShip::AddRightRotation(const FInputActionValue& Value)
{
	CurrentRotateInput = Value.Get<float>() * 100;
}

void APlayerShip::AddLeftRotation(const FInputActionValue& Value)
{
	CurrentRotateInput = -Value.Get<float>() * 100;
}

void APlayerShip::PerformShooting(const FInputActionValue& Value)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(BlasterShootingTimerHandle))
		return;

	GetWorld()->GetTimerManager().SetTimer(BlasterShootingTimerHandle, this,
	                                       &APlayerShip::FireBlasterShot,
	                                       60 / FireSpeedPerSec,
	                                       false);
}

void APlayerShip::SwitchAim(const FInputActionValue& Value)
{
	BIsAiming = !BIsAiming;

	if (BIsAiming)
	{
		CurrentCameraFOV = AimFOV;
	}
	else
	{
		CurrentCameraFOV = StandardFOV;
	}
}

void APlayerShip::UseFlare(const FInputActionValue& Value)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(FlareTimerHandle))
		return;

	GetWorld()->GetTimerManager().SetTimer(FlareTimerHandle, this, &APlayerShip::OnTimerSet, FlareCooldown, false);

	//TODO: sound
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FlareParticles, GetTransform());
	OnUsedFlare.Broadcast();
}

void APlayerShip::Dodge(const FInputActionValue& Value)
{
	if (CurrentTurnInput == FVector::Zero())
		return;

	FVector DodgeVector = FVector(0, -CurrentTurnInput.Y, 0);
	DodgeComponent->PerformDodge(DodgeVector);
}

void APlayerShip::SwitchGun(const FInputActionValue& Value)
{
	if (Value.Get<float>() > 0)
	{
		//++CurrentGunIndex;
	}
	else
	{
		//--CurrentGunIndex;
	}

	SetGun();
}

void APlayerShip::PerformTurn(float DeltaTime)
{
	FRotator TurnRotation = CurrentTurnInput.Rotation();
	CurrentTurnRotation = FMath::RInterpTo(CurrentTurnRotation, TurnRotation,
	                                       DeltaTime, InterpolationSpeed);
	if (BIsAiming)
	{
		AddActorLocalRotation(CurrentTurnRotation * DeltaTime * AimingTurnSpeed);
	}
	else
	{
		AddActorLocalRotation(CurrentTurnRotation * DeltaTime * TurnSpeed);
	}
}

void APlayerShip::PerformMovementForward(float DeltaTime)
{
	AddActorWorldOffset(GetActorForwardVector() * CurrentSpeed * DeltaTime, true);
}

void APlayerShip::PerformRotation(float DeltaTime)
{
	FRotator TurnRotation = FRotator(0, 0, CurrentRotateRotation.Pitch + CurrentRotateInput);
	CurrentRotateRotation = FMath::RInterpTo(CurrentRotateRotation, TurnRotation,
	                                         DeltaTime, RotationPower);

	AddActorLocalRotation(CurrentRotateRotation * DeltaTime);
}

void APlayerShip::ChangeCameraFOV(float DeltaTime)
{
	CameraComponent->FieldOfView = FMath::FInterpTo(CameraComponent->FieldOfView, CurrentCameraFOV, DeltaTime,
	                                                AimInterpolation);
}

void APlayerShip::OnTimerSet()
{
}

void APlayerShip::UpdateStats()
{
	MaxSpeed *= PlayerStats->SpeedModifier;
	FireSpeedPerSec *= PlayerStats->FireRateModifier;
	FlareCooldown /= PlayerStats->FlareCooldownModifier;
	HealthComponent->SetNewMaxHealth(HealthComponent->MaxHP * PlayerStats->HealthModifier);
}

void APlayerShip::OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	//TODO: check if other actor is boss or obstacle
	if (Cast<AProjectileBase>(OtherActor))
		return;

	if (UHealthComponent* Component = OtherActor->GetComponentByClass<UHealthComponent>())
	{
		Component->GetDamage(CollideDamage);
	}

	HealthComponent->GetDamage(CollideDamage);
}

void APlayerShip::PerformDamageCameraShake(float Damage)
{
	if (Damage < 10)
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(LowDamageCameraShake);
	else
		UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(HighDamageCameraShake);
}

// Called every frame
void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMovementForward(DeltaTime);
	PerformTurn(DeltaTime);
	PerformRotation(DeltaTime);
	ChangeCameraFOV(DeltaTime);
}

// Called to bind functionality to input
void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(AddSpeedAction, ETriggerEvent::Triggered, this, &APlayerShip::AddSpeed);
		EnhancedInputComponent->BindAction(DecreaseSpeedAction, ETriggerEvent::Triggered, this,
		                                   &APlayerShip::DecreaseSpeed);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &APlayerShip::Turn);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &APlayerShip::Turn);

		EnhancedInputComponent->BindAction(RotateRightAction, ETriggerEvent::Triggered, this,
		                                   &APlayerShip::AddRightRotation);
		EnhancedInputComponent->BindAction(RotateLeftAction, ETriggerEvent::Triggered, this,
		                                   &APlayerShip::AddLeftRotation);
		EnhancedInputComponent->BindAction(RotateLeftAction, ETriggerEvent::Completed, this,
		                                   &APlayerShip::AddLeftRotation);
		EnhancedInputComponent->BindAction(RotateRightAction, ETriggerEvent::Completed, this,
		                                   &APlayerShip::AddRightRotation);

		EnhancedInputComponent->BindAction(ShotAction, ETriggerEvent::Triggered, this,
		                                   &APlayerShip::PerformShooting);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &APlayerShip::SwitchAim);
		EnhancedInputComponent->BindAction(FlareAction, ETriggerEvent::Triggered, this, &APlayerShip::UseFlare);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &APlayerShip::Dodge);
	}
}

void APlayerShip::HandleDeath()
{
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetVisibility(false);
	EnhancedInputComponent->ClearActionBindings();
	CurrentSpeed = 0;
	CurrentRotateInput = 0;
	CurrentTurnInput = FVector::Zero();
}

float APlayerShip::GetCurrentSpeed()
{
	return CurrentSpeed;
}

FVector2D APlayerShip::GetPlayerAimDirection()
{
	FVector2D ScreenLocation;
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(OUT Hit, BlasterFireSocket->GetComponentLocation(),
	                                                 BlasterFireSocket->GetComponentLocation() + BlasterFireSocket->
	                                                 GetForwardVector() *
	                                                 AimDistance,
	                                                 ECollisionChannel::ECC_Visibility);

	if (bHit)
	{
		PlayerController->ProjectWorldLocationToScreen(
			Hit.Location, ScreenLocation);
	}
	else
	{
		PlayerController->ProjectWorldLocationToScreen(
			BlasterFireSocket->GetComponentLocation() + BlasterFireSocket->GetForwardVector() * AimDistance, ScreenLocation);
	}


	//DrawDebugLine(GetWorld(), Blaster->GetActorLocation(),
	//  Blaster->GetActorLocation() + Blaster->GetActorForwardVector() * 100, FColor::Red);


	return ScreenLocation;
}

void APlayerShip::ClampCurrentSpeed()
{
	if (CurrentSpeed <= MinSpeed)
		CurrentSpeed = MinSpeed;

	if (CurrentSpeed >= MaxSpeed)
		CurrentSpeed = MaxSpeed;
}
