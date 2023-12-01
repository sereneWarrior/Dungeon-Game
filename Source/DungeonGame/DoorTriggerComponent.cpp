// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerComponent.h"

UDoorTriggerComponent::UDoorTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UDoorTriggerComponent::OverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UDoorTriggerComponent::OverlapEnd);

	if (ObjectToUnlock)
	{
		Mover = ObjectToUnlock->GetComponentByClass<UMover>();
		if (!Mover)
		{
			UE_LOG(LogTemp, Error, TEXT("Mover set"));
		}
	}
}

void UDoorTriggerComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(UnlockTriggerObjectClass))
		Mover->ActivateMovement();
}

void UDoorTriggerComponent::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO: Store current overlapping actor?
	if (OtherActor->IsA(UnlockTriggerObjectClass)) 
		Mover->DeactivateMovement();
}