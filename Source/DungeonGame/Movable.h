// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Movable.generated.h"


UCLASS( Abstract )
class DUNGEONGAME_API UMovable : public UActorComponent
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

	UPROPERTY(EditAnywhere, Category = Mover)
	bool ShouldMove = false;

	virtual void MoveObject(float DeltaTime) PURE_VIRTUAL(UMovable::RemoveReplicatedSubObject,);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);
};
