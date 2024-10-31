// Fill out your copyright notice in the Description page of Project Settings.


#include "GamingArea.h"

#include "HealthComponent.h"
#include "PlayerShip.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGamingArea::AGamingArea()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Gameing Area"));
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGamingArea::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGamingArea::OnPlayerInArea);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGamingArea::OnPlayerOutOfArea);
}

void AGamingArea::OnPlayerOutOfArea(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex)
{
	APlayerShip* actor = Cast<APlayerShip>(OtherActor);

	if (actor && actor->HealthComponent->IsAlive())
	{
		OnPlayerOut.Broadcast();
	}
}

void AGamingArea::OnPlayerInArea(UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                 class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	APlayerShip* actor = Cast<APlayerShip>(OtherActor);
	
	if (actor && actor->HealthComponent->IsAlive())
	{
		OnPlayerIn.Broadcast();
	}
}

void AGamingArea::DestroyPlayer()
{
	Cast<APlayerShip>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->HealthComponent->Death();
}

// Called every frame
void AGamingArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
