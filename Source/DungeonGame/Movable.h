// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/TimelineComponent.h>

#include "Movable.generated.h"

UCLASS( )
class DUNGEONGAME_API AMovable : public AActor
{
	GENERATED_BODY()

protected:
	// Sets default values for this component's properties
	AMovable();

	// Called when the game starts
	virtual void BeginPlay() override;

	FTimeline Timeline;

	UPROPERTY(EditAnywhere, Category = Mover)
	UCurveFloat* CurveFloat;
	
	UFUNCTION()
	 void TimelineTest(float Alpha);

public:	

};
