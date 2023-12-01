// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "Mover.h"

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

	UMover* Mover;

protected:
	UDoorTriggerComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
