// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"
#include <Kismet/GameplayStatics.h>

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

	Owner = Cast<ADungeonGameCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("TraceComponent failed to set owner."))
	}

	Grabber = Owner->GetGrabber();
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Trace();

}

void UTraceComponent::Trace()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * TraceDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(TraceSphereRadius);
	FHitResult out_hitResult;

	// DEBUG Spheres
	// DrawDebugSphere(GetWorld(), start, TraceSphereRadius/2, 16, FColor::Red);
	// DrawDebugSphere(GetWorld(), end, TraceSphereRadius, 16, FColor::Blue);
	// TODO: Move check to variable in character class.
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

	if (out_hitResult.GetComponent() == Owner->GetTracedObject()->GetComponent())
		return;
	// TODO: Maybe use property to access hitresult in Character, remove dependency to Charactor
	Owner->SetTracedObject(out_hitResult);

	
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), 
		Owner->GetTracedObject()->GetActor() ?
		*Owner->GetTracedObject()->GetActor()->GetName() :
		TEXT("NULL"));

}

