// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "Movable.h"

#include "DoorTriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONGAME_API UDoorTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

	// TODO Set up class for unlock activating objects into 
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnlockTriggerObjectClass;

	UPROPERTY(EditAnywhere)
	AMovable* testobj;

protected:
	UDoorTriggerComponent() = default;

	// Called when the game starts
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
