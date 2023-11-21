// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "InputActionValue.h"

#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONGAME_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxGrabDist = 100.0f;

	UPROPERTY(EditAnywhere)
	float SweepingRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 100.0f;

	UPROPERTY(EditAnywhere)
	FVector HoldOffsetRight = FVector(50.0f, 0.0f, 0.0f);

	UPhysicsHandleComponent* PhysicsHandle;

	AActor* ReleaseSocketActor;

	bool isHolding = false;

public:	
	// Sets default values for this component's properties
	UGrabber();

	void Grab(const FInputActionValue& value, FHitResult* hitResult);

	void Release(const FInputActionValue& value, FHitResult* hitResult);

	void PlaceObjectOnSocket(FHitResult* hitResult);

	bool IsHoldingObject() const {
		return isHolding;
	};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
