// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

#include "ItemDataAsset.h"
#include "SpaceShipBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip = Cast<ASpaceShipBase>(GetOwner());

	if (!SpaceShip)
		UE_LOG(LogTemp, Error, TEXT("NO SPACE SHIP!!"));
	// ...
}


void UPlayerInventory::AddItem(UItemDataAsset* Item)
{
	PlayerItems.Add(Item);
	Item->PickUp(SpaceShip->PlayerStats);
	OnItemAdded.Broadcast(Item);
	UGameplayStatics::SpawnSound2D(this, ItemAddedSound);
}

void UPlayerInventory::RemoveItem(UItemDataAsset* Item)
{
	PlayerItems.Remove(Item);
	Item->Remove(SpaceShip->PlayerStats);
	OnItemRemoved.Broadcast(Item);
}

void UPlayerInventory::RemoveRandomItem()
{
	// TODO: Remove Random item 
}

void UPlayerInventory::RemoveAllItems()
{
	for (auto Element : PlayerItems)
	{
		Element->Remove(SpaceShip->PlayerStats);
		OnItemRemoved.Broadcast(Element);
		PlayerItems.Remove(Element);
	}
}

int UPlayerInventory::ItemCount(const UItemDataAsset* Item)
{
	int count = 0;
	for (const UItemDataAsset* Element : PlayerItems)
	{
		if (Element == Item) ++count;
	}

	UE_LOG(LogTemp, Display, TEXT("Found %i items"), count);
	return count;
}
