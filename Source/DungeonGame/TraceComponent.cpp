// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include <Kismet/GameplayStatics.h>
#include "DungeonGameCharacter.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	Grabber = Cast<ADungeonGameCharacter>(GetOwner())->GetGrabber();
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * 100.0f;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(100.0f);
	FHitResult out_hitResult;

	if (Grabber->IsHoldingObject())
	{
		GetWorld()->SweepSingleByChannel(out_hitResult,
			start,
			end,
			FQuat::Identity,
			ECC_GameTraceChannel3,
			Sphere);
	}
	else
	{
		GetWorld()->SweepSingleByChannel(out_hitResult,
				start,
				end,
				FQuat::Identity,
				ECC_GameTraceChannel4,
				Sphere);
	}
	
	
	if (out_hitResult.GetComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *out_hitResult.GetComponent()->GetName());
	}
	
}

