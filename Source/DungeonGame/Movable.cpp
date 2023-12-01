// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable.h"

// Sets default values for this component's properties
UMovable::UMovable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	
	
	//T->AddInterpFloat(CurveFloat, TimelineProgress);

}


// Called when the game starts
void UMovable::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	auto Actor = GetAttachmentRootActor();
// TODO: Put Timelines int owner class?
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("MoveObjectTimeline"));

	Timeline.AddInterpFloat(CurveFloat, ProgressUpdate);
	Timeline.SetPlayRate(1.0f / TransitionTime);
	Timeline.SetTimelineLength(1.0f);
}


void UMovable::TimelineTest(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline value: %f"), Alpha);
}

// Called every frame
void UMovable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Timeline.TickTimeline(DeltaTime);
}

void UMovable::SetShouldMove(bool NewShouldMove)
{
	if (NewShouldMove)
	{
		Timeline.Play();
		return;
	}
	Timeline.Reverse();
}

void UMovable::Activate()
{
	Timeline.Play();
}

void UMovable::Deactivate()
{
	Timeline.Reverse();
}


