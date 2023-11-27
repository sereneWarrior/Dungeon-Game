// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "EmitterManagerComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONGAME_API UEmitterManagerComponent : public UActorComponent
{
	GENERATED_BODY()

	UNiagaraComponent* FireEffect = nullptr;

	UPROPERTY(EditAnywhere)
	bool DEBUG_activateEmitter = false;

public:	
	// Sets default values for this component's properties
	UEmitterManagerComponent();

	bool GetIsEmitterActive();
	void SetEmitterActive(bool value);

	void InitializeEmitter();

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
