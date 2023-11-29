// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonGameCharacter.h"
#include "DungeonGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InflammableObject.h"
#include "InflammableObject.h"
#include "PushableObject.h"


//////////////////////////////////////////////////////////////////////////
// ADungeonGameCharacter

ADungeonGameCharacter::ADungeonGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(FirstPersonCameraComponent);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

}

void ADungeonGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
void ADungeonGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//////////////////////////////////////////////////////////////////////////// Input

void ADungeonGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonGameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonGameCharacter::Look);

		//Grab
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, Grabber, &UGrabber::Grab, &TracedObject);
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Completed, Grabber, &UGrabber::Release, &TracedObject);

		//Looking
		EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Triggered, this, &ADungeonGameCharacter::Interact);

		EnhancedInputComponent->BindAction(PushAction, ETriggerEvent::Triggered, this, &ADungeonGameCharacter::Push);
		
		EnhancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Started, this, &ADungeonGameCharacter::Forward);
		EnhancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Completed, this, &ADungeonGameCharacter::ForwardStop);
	}
}


void ADungeonGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ADungeonGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADungeonGameCharacter::Interact(const FInputActionValue& Value)
{
	//Call other Interact funtion? Just interact with single object f.e. door.
	if (!Grabber->IsHoldingObject())
		return;

	if (!TracedObject.GetActor()
		|| !TracedObject.GetActor()->Implements<UInteractable>())
		return;

	// Interact with flammable objects.
	if (auto flammable = Cast<AInflammableObject>(TracedObject.GetActor()))
		flammable->Interact(PhysicsHandle->GetGrabbedComponent()->GetOwner());

}

void ADungeonGameCharacter::Push(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Push"));
	if (Grabber->IsHoldingObject())
		return;


	if (!TracedObject.GetActor()
		|| !TracedObject.GetActor()->Implements<UInteractable>())
		return;
	// Open door completely
	if (auto pushable = Cast<APushableObject>(TracedObject.GetActor()))
		pushable->Interact();

}

void ADungeonGameCharacter::Forward(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("FW stopped"));
	if (Grabber->IsHoldingObject())
		return;


	if (!TracedObject.GetActor()
		|| !TracedObject.GetActor()->Implements<UInteractable>())
		return;

	// Open Door slightly
	if (auto pushable = Cast<APushableObject>(TracedObject.GetActor()))
		pushable->InteractionStarted();
}

void ADungeonGameCharacter::ForwardStop(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("FW stopped"));
	if (Grabber->IsHoldingObject())
		return;


	if (!TracedObject.GetActor()
		|| !TracedObject.GetActor()->Implements<UInteractable>())
		return;
	// Close Door
	if (auto pushable = Cast<APushableObject>(TracedObject.GetActor()))
		pushable->InteractionStopped();
}




