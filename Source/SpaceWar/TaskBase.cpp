// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskBase.h"

#include "Indicator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATaskBase::ATaskBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATaskBase::CompleteTask()
{
	OnCompleted.Broadcast(this);
	Destroy();
}

// Called when the game starts or when spawned
void ATaskBase::BeginPlay()
{
	TaskIndicator = GetWorld()->SpawnActor<AIndicator>(Indicator, GetActorLocation(), GetActorRotation());
	Super::BeginPlay();
}

// Called every frame
void ATaskBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
