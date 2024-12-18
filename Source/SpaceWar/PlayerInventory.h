// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInventory.generated.h"


class ASpaceGameMode;
class UItemDataAsset;
class ASpaceShipBase;
class APlayerItemClass;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	USoundBase* ItemAddedSound;

	void InitializeInventory();
	void AddItem(UItemDataAsset* Item);
	void RemoveItem(UItemDataAsset* Item);
	void RemoveRandomItem();
	void RemoveAllItems();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemsChanged, UItemDataAsset*, Value);

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FItemsChanged OnItemAdded;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FItemsChanged OnItemRemoved;
	
	UFUNCTION(BlueprintCallable)
	int ItemCount(const UItemDataAsset* Item);

private:
	UPROPERTY()
	ASpaceGameMode* GameMode; 
	UPROPERTY()
	ASpaceShipBase* SpaceShip;
};
