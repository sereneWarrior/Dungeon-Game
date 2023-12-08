// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable.h"

// Called when the game starts
void AMovable::BeginPlay()
{
	Super::BeginPlay();

	Mover = GetComponentByClass<UMover>();
	TimelineComponent = GetComponentByClass<UTimelineComponent>();

	// Set up default timeline if Actor does not have timeline created.
	if (!TimelineComponent)
	{
		TimelineComponent = NewObject<UTimelineComponent>(this, FName("MovementTimeline"));
		TimelineComponent->RegisterComponent();
	}

	FOnTimelineFloat onProgressUpdate;
	FOnTimelineEventStatic onTimelineFinishedFunc;

	onProgressUpdate.BindUFunction(Mover, FName("MoveObjectTimeline"));
	// TODO: Reverses play at evnet. Needs to be more customizable & extendable.
	onTimelineFinishedFunc.BindUFunction(this, FName("DisableMovement"));
	
	// General settings
	TimelineComponent->SetTimelineLength(1.0f);
	TimelineComponent->SetPlayRate(1.0f / TransitionTime);

	// Curve setting for movement 
	// TODO: Check if adding another curve makes problems
	if (CurveFloat)
		TimelineComponent->AddInterpFloat(CurveFloat, onProgressUpdate);

	TimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedFunc);
}

void AMovable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineComponent->TickComponent(DeltaTime, LEVELTICK_All, nullptr);
}

void AMovable::DisableMovement()
{
	TimelineComponent->SetComponentTickEnabled(false);
}

