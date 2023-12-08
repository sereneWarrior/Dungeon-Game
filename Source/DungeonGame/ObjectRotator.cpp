// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectRotator.h"
#include "Movable.h"

void UObjectRotator::BeginPlay()
{
	Super::BeginPlay();
	
	TargetRotation = owner->GetActorRotation() + FRotator(0.0f, RotationAngle, 0.0f);

}

void UObjectRotator::MoveObjectTimeline(float Value)
{
	owner->SetActorRelativeRotation(TargetRotation * Value);
}


