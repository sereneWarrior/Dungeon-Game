// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "Mover.h"
#include "Movable.h"

#include "PushableObject.generated.h"


UCLASS()
class DUNGEONGAME_API APushableObject : public AMovable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int MaxPushCount = 2;

	int currentPushCount = 0;

public:
	// Sets default values for this actor's properties
	APushableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void HideObjectFromTracing();


public:
	void InteractionStarted();

	UFUNCTION()
	void InteractionStopped();

};