// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
}