// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeamsEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETeamsEnum : uint8
{
	Ally = 0 UMETA(DisplayName = "Ally"),
	Enemy = 1 UMETA(DisplayName = "Enemy")
};
