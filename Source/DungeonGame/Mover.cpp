// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	
	//TimelineComponent = owner->GetComponentByClass<UTimelineComponent>();
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("MoveObjectTimeline"));

	// Set up default timeline if Actor does not have timeline created.
	if (!TimelineComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Set up timeline component"));
		TimelineComponent = NewObject<UTimelineComponent>(owner, FName("Timeline"));
		TimelineComponent->RegisterComponent();
	}
	
	TimelineComponent->SetTimelineLength(1.0f);
	TimelineComponent->SetPlayRate(1.0f / TransitionTime);
	TimelineComponent->AddInterpFloat(CurveFloat, ProgressUpdate);
}


void UMover::TimelineTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline Test"));
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimelineComponent->TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMover::ActivateMovement()
{
		TimelineComponent->Play();
}

void UMover::DeactivateMovement()
{
	TimelineComponent->Reverse();
}
