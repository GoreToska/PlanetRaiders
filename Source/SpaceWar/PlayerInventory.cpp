// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

#include "ItemDataAsset.h"
#include "SpaceGameInstance.h"
#include "SpaceGameMode.h"
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
	GameMode = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(this));
	GameInstance = Cast<USpaceGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	InitializeInventory();

	if (!SpaceShip)
		UE_LOG(LogTemp, Error, TEXT("NO SPACE SHIP!!"));
	// ...
}


void UPlayerInventory::InitializeInventory()
{
	for (auto Element : GameInstance->PlayerItems)
	{
		Element->PickUp(SpaceShip->PlayerStats);
		OnItemAdded.Broadcast(Element);
	}
}

void UPlayerInventory::AddItem(UItemDataAsset* Item)
{
	GameInstance->PlayerItems.Add(Item);
	Item->PickUp(SpaceShip->PlayerStats);
	OnItemAdded.Broadcast(Item);
	UGameplayStatics::SpawnSound2D(this, ItemAddedSound);
}

void UPlayerInventory::RemoveItem(UItemDataAsset* Item)
{
	GameInstance->PlayerItems.Remove(Item);
	Item->Remove(SpaceShip->PlayerStats);
	OnItemRemoved.Broadcast(Item);
}

void UPlayerInventory::RemoveRandomItem()
{
	// TODO: Remove Random item 
}

void UPlayerInventory::RemoveAllItems()
{
	for (auto Element : GameInstance->PlayerItems)
	{
		Element->Remove(SpaceShip->PlayerStats);
		OnItemRemoved.Broadcast(Element);
		GameInstance->PlayerItems.Remove(Element);
	}
}

/*int UPlayerInventory::ItemCount(const UItemDataAsset* Item)
{
	int count = 0;
	for (const UItemDataAsset* Element : GameInstance->PlayerItems)
	{
		if (Element == Item) ++count;
	}

	UE_LOG(LogTemp, Display, TEXT("Found %i items"), count);
	return count;
}*/
