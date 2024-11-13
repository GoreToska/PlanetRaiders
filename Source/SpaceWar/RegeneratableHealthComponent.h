#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "RegeneratableHealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPACEWAR_API URegeneratableHealthComponent : public UHealthComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTimerHandle HealTimerHandle;
	UPROPERTY(EditAnywhere)
	float HealPerSecond = 10;
	UPROPERTY(EditAnywhere)
	float HealDelay = 10;

	UFUNCTION()
	void StartHealTimer(float damage);
	UFUNCTION()
	void HealProcess();

public:
	virtual void BeginPlay() override;
};
