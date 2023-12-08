// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/TimelineComponent.h>
#include "Mover.h"

#include "Movable.generated.h"


UCLASS(Abstract)
class DUNGEONGAME_API AMovable : public AActor
{
	GENERATED_BODY()

protected:
	AMovable() = default;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	UMover* Mover;
	
	// TODO: Create struct for time line event? Event: Time, Obj, FunctionName

	UPROPERTY(EditAnywhere, Category = Movement)
	float TransitionTime = 5.0f;

	UPROPERTY(BlueprintReadWrite)
	UTimelineComponent* TimelineComponent;

	UPROPERTY(EditAnywhere, Category = Movement)
	UCurveFloat* CurveFloat;
	
	UFUNCTION()
	virtual void DisableMovement();

public:	
	virtual void Tick(float DeltaTime) override;

	void PlayTimeline() { TimelineComponent->Play(); }
	void ReverseTimeline() { TimelineComponent->Reverse(); }
	void StopTimeline() { TimelineComponent->Stop(); }


};
