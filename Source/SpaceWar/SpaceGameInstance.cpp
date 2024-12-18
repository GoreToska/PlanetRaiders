// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceGameInstance.h"

int USpaceGameInstance::GetSeconds()
{
	int Seconds = CurrentTime % 60;
	return Seconds;
}

int USpaceGameInstance::GetMinutes()
{
	int Minutes = CurrentTime / 60;
	return Minutes;
}

void USpaceGameInstance::StartTimer()
{
	UE_LOG(LogTemp, Display, TEXT("StartedTimer"));
	GetWorld()->GetTimerManager().SetTimer(WorldTimer, this, &USpaceGameInstance::OnTimerTick, 1, true);
}

void USpaceGameInstance::StopTimer()
{
	if (WorldTimer.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(WorldTimer);
}

int USpaceGameInstance::GetCurrentUpgrade()
{
	return CurrentUpgrade;
}

void USpaceGameInstance::OnTimerTick()
{
	++CurrentTime;
	OnTimerChanged.Broadcast();

	if (CurrentTime >= CurrentUpgrade * TimeToUpgrade)
	{
		++CurrentUpgrade;
		OnUpgraded.Broadcast(CurrentUpgrade);
	}
}

void USpaceGameInstance::NewGame()
{
	CurrentTime = 0;
	CurrentUpgrade = 1;
}
