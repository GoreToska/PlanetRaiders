#include "RegeneratableHealthComponent.h"

void URegeneratableHealthComponent::StartHealTimer(float damage)
{
	GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this,
	                                       &URegeneratableHealthComponent::HealProcess, 1, true, HealDelay);
}

void URegeneratableHealthComponent::HealProcess()
{
	if(CurrentHP==MaxHP || !IsAlive())
		return;

	UE_LOG(LogTemp, Display, TEXT("Healing"));
	GetHeal(HealPerSecond);
}

void URegeneratableHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	OnGetDamage.AddDynamic(this,&URegeneratableHealthComponent::StartHealTimer);
}
