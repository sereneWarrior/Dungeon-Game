// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"

#include "Interactable.h"
#include "EmitterManagerComponent.h"

#include "InflammableObject.generated.h"


/**
 * 
 */
UCLASS()
class DUNGEONGAME_API AInflammableObject : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()
	
	UEmitterManagerComponent* EmitterManager;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void Interact(AActor* other);

	bool IsActive() const;
	void SetActivity(bool value);
};
