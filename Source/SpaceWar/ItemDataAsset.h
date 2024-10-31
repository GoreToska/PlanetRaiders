// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

class UPlayerStats;
/**
 * 
 */
UCLASS()
class SPACEWAR_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UTexture2D* GetImage();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetItemName();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetItemDescription();
	
	virtual void PickUp(UPlayerStats* PlayerStats);
	virtual void Remove(UPlayerStats* PlayerStats);
private:
	UPROPERTY(EditAnywhere)
	UTexture2D* Image;
	UPROPERTY(EditAnywhere)
	FString Name;
	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	bool IncreaseDamage = false;
	UPROPERTY(EditAnywhere)
	bool IncreaseHealth = false;
	UPROPERTY(EditAnywhere)
	bool IncreaseSpeed = false;
	UPROPERTY(EditAnywhere)
	bool IncreaseFireRate = false;
	UPROPERTY(EditAnywhere)
	bool IncreaseFlare = false;
};
