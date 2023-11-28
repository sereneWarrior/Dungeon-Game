// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSlider.h"

void UObjectSlider::BeginPlay()
{
	Super::BeginPlay();

	OriginLoc = owner->GetActorLocation();
}

void UObjectSlider::MoveObject(float DeltaTime)
{
	FVector LocationAfterTransition = FMath::VInterpConstantTo(owner->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), TransitionTime);
	owner->SetActorLocation(LocationAfterTransition);
}

void UObjectSlider::MoveObjectTimeline(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Timeline value: %f"), Value);
	TargetLocation = OriginLoc + TransitionOffset * Value;
	FVector LocationAfterTransition = FMath::Lerp(owner->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds());
	owner->SetActorLocation(TargetLocation);
}