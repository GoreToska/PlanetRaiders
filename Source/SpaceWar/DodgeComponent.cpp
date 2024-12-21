// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeComponent.h"

#include "HomingProjectile.h"
#include "SpaceShipBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDodgeComponent::UDodgeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDodgeComponent::DodgeRockets()
{
	DrawDebugSphere(GetWorld(),
	                OwningActor->GetActorLocation(),
	                DodgeDistance, 32, FColor::Red, false, 10);
	TArray<AActor*> Actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	ActorsToIgnore.Add(OwningActor);
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		OwningActor->GetActorLocation(),
		DodgeDistance,
		ObjectTypes,
		AActor::StaticClass(),
		ActorsToIgnore,
		Actors);

	if (Actors.Num() <= 0)
	{
		return;
	}

	for (AActor* a : Actors)
	{
		AHomingProjectile* projectile = Cast<AHomingProjectile>(a);

		if (!projectile)
			return;

		projectile->ClearProjectileHomingTarget();
	}
}

// Called when the game starts
void UDodgeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DodgeCurve)
	{
		DodgeCurve->GetTimeRange(MinDodgeTime, MaxDodgeTime);
		Cooldown = MaxDodgeTime;
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
			return;
		} 

		float CurveValue = DodgeCurve->GetFloatValue(DodgeTime);
		float DeltaCurve = CurveValue - PrevDodgeTime;
		PrevDodgeTime = CurveValue;
		OwningActor->AddActorLocalOffset(DodgeSideModifier * DodgeSpeed * DeltaTime * DeltaCurve);
		DodgeTime += DeltaTime;
	}

	UE_LOG(LogTemp, Display, TEXT("%f"), DodgeTime);
}

void UDodgeComponent::PerformDodge(const FVector& InputVector)
{
	if (DodgeCurve == nullptr)
	{
		return;
	}
	if (bIsDodging) return;

	DodgeSideModifier = InputVector;
	DodgeSideModifier.Normalize();
	bIsDodging = true;
	DodgeRockets();
	UGameplayStatics::SpawnSoundAttached(DodgeSound, GetOwner()->GetRootComponent());
}
