// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <Components/TimelineComponent.h>

#include "Mover.generated.h"

UCLASS(Abstract)
class DUNGEONGAME_API UMover : public USceneComponent
{
	GENERATED_BODY()

protected:
	// Sets default values for this component's properties
	UMover();

	AActor* owner;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Mover)
	float TransitionTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)
	bool ShouldMove = false;

	FTimeline Timeline;

	FTimeline* CastedTimeline;

	UPROPERTY(BlueprintReadWrite)
	class UTimelineComponent* TimelineComponent;

	UPROPERTY(EditAnywhere, Category = Mover)
	UCurveFloat* CurveFloat;

	// DEPRECATED
	virtual void MoveObject(float DeltaTime) PURE_VIRTUAL(UMover::RemoveReplicatedSubObject, );

	virtual void MoveObjectTimeline(float Alpha) PURE_VIRTUAL(UMover::RemoveReplicatedSubObject, );
	
	UFUNCTION(BlueprintCallable)
	void TimelineTest();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateMovement();
	void DeactivateMovement();
};