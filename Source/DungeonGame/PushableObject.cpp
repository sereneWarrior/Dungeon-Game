// Fill out your copyright notice in the Description page of Project Settings.


#include "PushableObject.h"

// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APushableObject::BeginPlay()
{
	Super::BeginPlay();
	Mover = GetComponentByClass<UMover>();
}

// Called every frame
void APushableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushableObject::Interact(AActor* otherActor)
{
	Mover->ActivateMovement();
}

void APushableObject::InteractionStopped()
{
	UE_LOG(LogTemp, Warning, TEXT("TimelineEvent from owner"));
	if (currentPushCount >= MaxPushCount)
		return;
	Mover->DeactivateMovement();
}

void APushableObject::InteractionStarted()
{
	currentPushCount++;
	Mover->ActivateMovement();
	
}
