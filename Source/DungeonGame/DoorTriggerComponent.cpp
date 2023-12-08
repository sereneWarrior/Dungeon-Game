// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTriggerComponent.h"

void UDoorTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UDoorTriggerComponent::OverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UDoorTriggerComponent::OverlapEnd);

	if (!testobj)
		UE_LOG(LogTemp, Error, TEXT("Unlocking object not set for: %s, Compoent: %s"),
			*GetOwner()->GetName(),
			*GetName());
}

void UDoorTriggerComponent::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor->IsA(UnlockTriggerObjectClass))
		testobj->PlayTimeline();
		
}

void UDoorTriggerComponent::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// TODO: Store current overlapping actor? To not react on additional overlap.
	if (OtherActor->IsA(UnlockTriggerObjectClass)) 
		testobj->StopTimeline();
}