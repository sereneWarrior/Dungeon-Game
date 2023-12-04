// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable.h"

// Sets default values for this component's properties
AMovable::AMovable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	

	//T->AddInterpFloat(CurveFloat, TimelineProgress);

}


// Called when the game starts
void AMovable::BeginPlay()
{
	Super::BeginPlay();


// TODO: Put Timelines int owner class?
	/*FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("MoveObjectTimeline"));

	Timeline.AddInterpFloat(CurveFloat, ProgressUpdate);
	Timeline.SetPlayRate(1.0f / TransitionTime);
	Timeline.SetTimelineLength(1.0f);*/
}


void AMovable::TimelineTest(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline value: %f"), Alpha);
}


