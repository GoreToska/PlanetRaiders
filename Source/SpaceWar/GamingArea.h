// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamingArea.generated.h"

class USphereComponent;

UCLASS()
class SPACEWAR_API AGamingArea : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGamingArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UFUNCTION()
	void OnPlayerOutOfArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnPlayerInArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void DestroyPlayer();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerOutOfArea);
	UPROPERTY(BlueprintAssignable)
	FPlayerOutOfArea OnPlayerOut;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerInArea);
	UPROPERTY(BlueprintAssignable)
	FPlayerInArea OnPlayerIn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeToReturn = 10;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
