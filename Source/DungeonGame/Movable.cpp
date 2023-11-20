// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable.h"

// Sets default values for this component's properties
UMovable::UMovable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UMovable::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	
}


// Called every frame
void UMovable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		MoveObject(DeltaTime);
	}
}

void UMovable::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

