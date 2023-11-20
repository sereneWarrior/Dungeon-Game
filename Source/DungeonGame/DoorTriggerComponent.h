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

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> UnlockTriggerObjectClass;

	UPROPERTY(EditAnywhere)
	AActor* ObjectToUnlock;

	UMovable* Mover;

	AActor* GetTriggeringActor() const;

protected:
	UDoorTriggerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable)
	void SetMover(UMovable* Mover);
};
