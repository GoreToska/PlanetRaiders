// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldDifficulty.h"

// Sets default values
AWorldDifficulty::AWorldDifficulty()
{
}

int AWorldDifficulty::GetSeconds()
{
	int Seconds = CurrentTime % 60;
	return Seconds;
}

int AWorldDifficulty::GetMinutes()
{
	int Minutes = CurrentTime / 60;
	return Minutes;
}

int AWorldDifficulty::GetCurrentUpgrade()
{
	return CurrentUpgrade;
}

// Called when the game starts or when spawned
void AWorldDifficulty::BeginPlay()
{
	Super::BeginPlay();

	CurrentTime = 0;
	CurrentUpgrade = 1;
	GetWorld()->GetTimerManager().SetTimer(WorldTimer, this, &AWorldDifficulty::OnTimerTick, 1, true);
}

void AWorldDifficulty::OnTimerTick()
{
	++CurrentTime;
	OnTimerChanged.Broadcast();

	if (CurrentTime >= CurrentUpgrade * TimeToUpgrade)
	{
		++CurrentUpgrade;
		OnUpgraded.Broadcast(CurrentUpgrade);
	}
}

// Called every frame
void AWorldDifficulty::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
