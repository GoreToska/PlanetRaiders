// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShipBase.h"
#include "EnemySpaceShip.generated.h"

class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class SPACEWAR_API AEnemySpaceShip : public ASpaceShipBase
{
	GENERATED_BODY()

public:
	AEnemySpaceShip();
	void FollowTarget(AActor* Actor);
	void StopFollow();
	bool HasTarget();
protected:
	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnCollide(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY()
	bool bHasTarget = false;
};
