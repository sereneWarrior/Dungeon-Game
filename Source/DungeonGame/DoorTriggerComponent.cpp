// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerComponent.h"

UDoorTriggerComponent::UDoorTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ObjectToUnlock)
	{
		Mover = ObjectToUnlock->GetComponentByClass<UMovable>();
		if (Mover)
		{
			UE_LOG(LogTemp, Warning, TEXT("Mover set"));
		}
	}
}

void UDoorTriggerComponent::SetMover(UMovable* NewMover)
{
	Mover = NewMover;
}

void UDoorTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!Mover)
		return;

	AActor* triggeringActor = GetTriggeringActor();
	if (triggeringActor != nullptr)
		Mover->SetShouldMove(true);	
	else
		Mover->SetShouldMove(false);
}

AActor* UDoorTriggerComponent::GetTriggeringActor() const
{
	TArray<AActor*> actors;
	GetOverlappingActors(actors, UnlockTriggerObjectClass);

	return actors.IsEmpty() ?
		nullptr :
		actors[0];
}