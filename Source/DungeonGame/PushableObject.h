// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "Mover.h"

#include "PushableObject.generated.h"


UCLASS()
class DUNGEONGAME_API APushableObject : public AActor, public IInteractable
{
	GENERATED_BODY()

	UMover* Mover;

	UPROPERTY(EditAnywhere)
	int MaxPushCount = 2;

	int currentPushCount = 0;

	bool moveForward = true;
	
public:	
	// Sets default values for this actor's properties
	APushableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* otherActor = nullptr);

	UFUNCTION()
	void InteractionStopped();
	void InteractionStarted();

	void SetAction(bool moveFw) { moveForward = moveFw; }
};
