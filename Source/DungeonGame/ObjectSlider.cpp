// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSlider.h"

void UObjectSlider::BeginPlay()
{
	Super::BeginPlay();

	FVector currentLoc = owner->GetActorLocation();
	TargetLocation = currentLoc + TransitionOffset;
	TranslationSpeed = FVector::Distance(currentLoc, TargetLocation) / TransitionTime;
}

void UObjectSlider::MoveObject(float DeltaTime)
{
	FVector LocationAfterTransition = FMath::VInterpConstantTo(owner->GetActorLocation(), TargetLocation, GetWorld()->GetDeltaSeconds(), TransitionTime);
	owner->SetActorLocation(LocationAfterTransition);
}
