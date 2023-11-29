// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectRotator.h"
#include "PushableObject.h"

void UObjectRotator::BeginPlay()
{
	Super::BeginPlay();

	FOnTimelineEvent TestEvent;
	if (auto pushable = Cast<APushableObject>(owner))
	{
		TestEvent.BindUFunction(pushable, FName("PrintEvent"));
		Timeline.AddEvent(0.2f, TestEvent);
	}
	
	
	TargetRotation = owner->GetActorRotation() + FRotator(0.0f, RotationAngle, 0.0f);

}

void UObjectRotator::MoveObject(float DeltaTime)
{
	FRotator RotationAfterTransition = FMath::RInterpConstantTo(owner->GetActorRotation(), TargetRotation, DeltaTime, TransitionTime);
	owner->SetActorRotation(RotationAfterTransition);
}

void UObjectRotator::MoveObjectTimeline(float Value)
{
	owner->SetActorRelativeRotation(TargetRotation * Value);
}

void UObjectRotator::PrintEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("TimelineEvent"));
}
