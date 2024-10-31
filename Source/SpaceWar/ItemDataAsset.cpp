// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataAsset.h"

#include "PlayerStats.h"

UTexture2D* UItemDataAsset::GetImage()
{
	return Image;
}

FString UItemDataAsset::GetItemName()
{
	return Name;
}

FString UItemDataAsset::GetItemDescription()
{
	return Description;
}

void UItemDataAsset::PickUp(UPlayerStats* PlayerStats)
{
	if (IncreaseDamage)
		PlayerStats->ChangeDamage(PlayerStats->IncreaseExponent);
	if (IncreaseHealth)
		PlayerStats->ChangeHealth(PlayerStats->IncreaseExponent);
	if (IncreaseSpeed)
		PlayerStats->ChangeSpeed(PlayerStats->IncreaseExponent);
	if (IncreaseFireRate)
		PlayerStats->ChangeFireRate(PlayerStats->IncreaseExponent);
	if (IncreaseFlare)
		PlayerStats->ChangeFlareCooldown(PlayerStats->IncreaseExponent);
}

void UItemDataAsset::Remove(UPlayerStats* PlayerStats)
{
	if (IncreaseDamage)
		PlayerStats->ChangeDamage(PlayerStats->DecreaseExponent);
	if (IncreaseHealth)
		PlayerStats->ChangeHealth(PlayerStats->DecreaseExponent);
	if (IncreaseSpeed)
		PlayerStats->ChangeSpeed(PlayerStats->DecreaseExponent);
	if (IncreaseFireRate)
		PlayerStats->ChangeFireRate(PlayerStats->DecreaseExponent);
	if (IncreaseFlare)
		PlayerStats->ChangeFlareCooldown(PlayerStats->DecreaseExponent);
}
