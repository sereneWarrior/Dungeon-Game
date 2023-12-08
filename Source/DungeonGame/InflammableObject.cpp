// Fill out your copyright notice in the Description page of Project Settings.


#include "InflammableObject.h"


void AInflammableObject::BeginPlay()
{
	EmitterManager = GetComponentByClass<UEmitterManagerComponent>();
	if (!EmitterManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Emitter missing"));
	}
	// Emitter needs to call initialize function since BeginPlay seems not to work properly.
	// It was only called on value updates but not when game started.
	EmitterManager->InitializeEmitter();
}

void AInflammableObject::InteractionStarted(AActor* other)
{
	auto otherFlammable = Cast<AInflammableObject>(other);
	
	// If both emitter are either on or off nothing needs to be done.
	if (!otherFlammable ||
		EmitterManager->GetIsEmitterActive() == otherFlammable->IsActive())
		return;

	EmitterManager->GetIsEmitterActive() ?
		otherFlammable->SetActivity(true):
			SetActivity(true);
}

bool AInflammableObject::IsActive() const
{
	return EmitterManager->GetIsEmitterActive();
}

void AInflammableObject::SetActivity(bool value)
{
	EmitterManager->SetEmitterActive(value);
}
