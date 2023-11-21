// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Grabber.h"
#include "DungeonGameCharacter.h"

#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONGAME_API UTraceComponent : public USceneComponent
{
	GENERATED_BODY()

	UGrabber* Grabber;

	ADungeonGameCharacter* Owner;

	void Trace();

public:	
	// Sets default values for this component's properties
	UTraceComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
