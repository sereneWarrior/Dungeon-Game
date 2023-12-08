// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"

#include "ObjectRotator.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONGAME_API UObjectRotator : public UMover
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Movement)
	float RotationAngle;

	FRotator TargetRotation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void MoveObjectTimeline(float Value) override;


};
