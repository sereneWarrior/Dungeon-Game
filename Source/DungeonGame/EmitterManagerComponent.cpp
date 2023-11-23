// Fill out your copyright notice in the Description page of Project Settings.


#include "EmitterManagerComponent.h"

// Sets default values for this component's properties
UEmitterManagerComponent::UEmitterManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UEmitterManagerComponent::GetIsEmitterActive()
{
	return FireEffect->IsActive();
}

void UEmitterManagerComponent::SetEmitterActive(bool value)
{
	if (!FireEffect)
		return;
	FireEffect->Activate(value);
}

void UEmitterManagerComponent::InitializeEmitter()
{
	FireEffect = GetOwner()->GetComponentByClass<UNiagaraComponent>();
}

// Called every frame
void UEmitterManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// For debug
	//FireEffect->SetActive(DEBUG_activateEmitter);
}

