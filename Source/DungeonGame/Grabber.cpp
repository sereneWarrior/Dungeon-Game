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
}

void UGrabber::Grab(const FInputActionValue& value, FHitResult* hitResult)
{
	if (PhysicsHandle == nullptr
		|| !hitResult->GetComponent()
		|| !hitResult->GetComponent()->ComponentHasTag("Grabbable"))
	{
		return;
	}

	UPrimitiveComponent* hitComponent = hitResult->GetComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Target: %s"), *hitComponent->GetName());
	hitComponent->WakeAllRigidBodies();

	hitComponent->SetSimulatePhysics(true);
	PhysicsHandle->GrabComponentAtLocationWithRotation(hitResult->GetComponent(),
		NAME_None,
		hitResult->ImpactPoint,
		hitComponent->GetComponentRotation());
	isHolding = true;

}

void UGrabber::Release(const FInputActionValue& value, FHitResult* hitResult)
{
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Handle missing"));
		return;
	}

	PlaceObjectOnSocket(hitResult);

	PhysicsHandle->ReleaseComponent();
	isHolding = false;
}

void UGrabber::PlaceObjectOnSocket(FHitResult* hitResult)
{
	if (!hitResult->GetActor() || !hitResult->GetActor()->ActorHasTag("Socket"))
		return;

	UStaticMeshComponent* mesh = hitResult->GetActor()->GetComponentByClass<UStaticMeshComponent>();
	auto socketLocation = mesh->GetSocketTransform(FName("ReleaseLoc")).GetLocation();
	auto socketRotation = mesh->GetSocketTransform(FName("ReleaseLoc")).GetRotation();

	PhysicsHandle->GetGrabbedComponent()->GetOwner()->SetActorLocation(socketLocation);
	PhysicsHandle->GetGrabbedComponent()->GetOwner()->SetActorRotation(socketRotation);
	PhysicsHandle->GetGrabbedComponent()->SetSimulatePhysics(false);
}