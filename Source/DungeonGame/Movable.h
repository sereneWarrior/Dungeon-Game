// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/TimelineComponent.h>

#include "Movable.generated.h"

UCLASS( Abstract )
class DUNGEONGAME_API UMovable : public USceneComponent
{
	GENERATED_BODY()

protected:
	// Sets default values for this component's properties
	UMovable();

	AActor* owner;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Mover)
	float TransitionTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)
	bool ShouldMove = false;

	FTimeline Timeline;

	UPROPERTY(EditAnywhere, Category = Mover)
	UCurveFloat* CurveFloat;
	
	// DEPRECATED
	virtual void MoveObject(float DeltaTime) PURE_VIRTUAL(UMovable::RemoveReplicatedSubObject,);
	
	virtual void MoveObjectTimeline(float Alpha) PURE_VIRTUAL(UMovable::RemoveReplicatedSubObject, );
	UFUNCTION()
	 void TimelineTest(float Alpha);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);
};
