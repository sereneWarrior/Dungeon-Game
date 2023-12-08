// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSlider.h"
#include "Movable.h"

void UObjectSlider::BeginPlay()
{
	Super::BeginPlay();

	OriginLoc = owner->GetActorLocation();
}

void UObjectSlider::MoveObjectTimeline(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline value: %f"), Value);
	TargetLocation = OriginLoc + TransitionOffset * Value;
	FVector LocationAfterTransition = FMath::Lerp(owner->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds());
	owner->SetActorLocation(TargetLocation);
}