// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// On overlap with owner?
	AActor* owner = GetOwner();

	if (ShouldMove)
	{
		FVector currentLoc = owner->GetActorLocation();
		FVector targetLocation = currentLoc + TransitionOffset;
		float speed = FVector::Distance(currentLoc, targetLocation) / TransitionTime;

		FVector LocationAfterTransition = FMath::VInterpConstantTo(currentLoc, targetLocation, DeltaTime, speed);
		owner->SetActorLocation(LocationAfterTransition);

	}
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

