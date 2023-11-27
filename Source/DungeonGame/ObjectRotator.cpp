// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectRotator.h"

void UObjectRotator::BeginPlay()
{
	Super::BeginPlay();

	TargetRotation = owner->GetActorRotation() + FRotator(0.0f, RotationAngle, 0.0f);

}

void UObjectRotator::MoveObject(float DeltaTime)
{
	FRotator RotationAfterTransition = FMath::RInterpConstantTo(owner->GetActorRotation(), TargetRotation, DeltaTime, TransitionTime);
	owner->SetActorRotation(RotationAfterTransition);
}
