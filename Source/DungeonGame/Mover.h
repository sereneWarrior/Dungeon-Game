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
	UMover() = default;

	AActor* owner;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void MoveObjectTimeline(float Alpha) PURE_VIRTUAL(UMover::RemoveReplicatedSubObject, );

};