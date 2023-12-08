// Fill out your copyright notice in the Description page of Project Settings.


#include "PushableObject.h"
#include <Components/TimelineComponent.h>

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
	
	FOnTimelineEvent onTimelineEvent;

	onTimelineEvent.BindUFunction(this, FName("InteractionStopped"));
	TimelineComponent->AddEvent(0.1f, onTimelineEvent);

}

void APushableObject::HideObjectFromTracing()
{
	if (TimelineComponent->GetPlaybackPosition() >= 0.0f)
		SetActorEnableCollision(false);// TODO: Put into interactible?
}

void APushableObject::InteractionStarted()
{
	currentPushCount++;
	TimelineComponent->Play();
}

// Called from timeline.
void APushableObject::InteractionStopped()
{
	if (currentPushCount >= MaxPushCount)
	{
		// TODO: Disable Tracking channel
		return;
	}

	TimelineComponent->Reverse();
}

