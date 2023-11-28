// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movable.h"
#include "ObjectSlider.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONGAME_API UObjectSlider : public UMovable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Mover)
	FVector TransitionOffset;

	FVector TargetLocation;

	float TranslationSpeed;

	FVector OriginLoc;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void MoveObject(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void MoveObjectTimeline(float Value) override;
};
