// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DungeonGameCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	PhysicsHandle = Cast<ADungeonGameCharacter>(GetOwner())->GetPhysicsHandleComponent();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Handle missing"));
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector TargetLocation = GetComponentLocation() + HoldOffsetRight + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

	// Set socket object to place physics target
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		//TODO: Is there a better way to implement setting ReleaseSocketActor
		FHitResult hitResult;
		if (DetectedSocketObject(hitResult))
		{
			ReleaseSocketActor = hitResult.GetActor();
		}
		else
		{
			ReleaseSocketActor = nullptr;
		}
	}
}

void UGrabber::Grab()
{
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Handle missing"));
		return;
	}

	FHitResult hitResult;
	if (DetectedGrabbableObject(hitResult))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Grab activated"));
		UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *hitResult.GetActor()->GetName());
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->WakeAllRigidBodies();

		hitComponent->SetSimulatePhysics(true);
		PhysicsHandle->GrabComponentAtLocationWithRotation(hitResult.GetComponent(),
			NAME_None,
			hitResult.ImpactPoint,
			hitResult.GetComponent()->GetComponentRotation());
		isHolding = true;
	}
}

void UGrabber::Release()
{
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Handle missing"));
		return;
	}
	PlaceObjectOnSocket();

	PhysicsHandle->ReleaseComponent();
	isHolding = false;
}

void UGrabber::PlaceObjectOnSocket()
{
	if (ReleaseSocketActor == nullptr)
		return;

	UStaticMeshComponent* mesh = ReleaseSocketActor->GetComponentByClass<UStaticMeshComponent>();
	auto socketLocation = mesh->GetSocketTransform(FName("ReleaseLoc")).GetLocation();
	auto socketRotation = mesh->GetSocketTransform(FName("ReleaseLoc")).GetRotation();
	
	PhysicsHandle->GetGrabbedComponent()->GetOwner()->SetActorLocation(socketLocation);
	PhysicsHandle->GetGrabbedComponent()->GetOwner()->SetActorRotation(socketRotation);
	PhysicsHandle->GetGrabbedComponent()->SetSimulatePhysics(false);
}

bool UGrabber::DetectedGrabbableObject(FHitResult& out_hitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDist;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(SweepingRadius);

	return GetWorld()->SweepSingleByChannel(out_hitResult,
		start,
		end,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
}

bool UGrabber::DetectedSocketObject(FHitResult& out_hitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * 100.0f;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(100.0f);

	return GetWorld()->SweepSingleByChannel(out_hitResult,
		start,
		end,
		FQuat::Identity,
		ECC_GameTraceChannel3,
		Sphere);
}