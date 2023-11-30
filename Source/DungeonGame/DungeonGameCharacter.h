// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Grabber.h"

#include "DungeonGameCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ADungeonGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PhysicsHandle, meta = (AllowPrivateAccess = "true"))
	UPhysicsHandleComponent* PhysicsHandle;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* GrabAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;

	/** Push Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PushAction;

	/** Push Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ForwardAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grabber, meta = (AllowPrivateAccess = "true"))
	UGrabber* Grabber;

	// TODO: Think about better way to set and store the necessary trace channels.
	//UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> DefaultTraceChannel = ECollisionChannel::ECC_GameTraceChannel4;

	// TODO: Tracing data struct?
	// TODO: Better have it type Actor?
	FHitResult TracedObject;
	int CurrentTraceChannel = DefaultTraceChannel;

public:
	ADungeonGameCharacter();
	
	FHitResult* GetTracedObject() { return &TracedObject; }

	void SetTracedObject(FHitResult &hitResult) { TracedObject = hitResult; }

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;


protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void Interact(const FInputActionValue& Value);

	/** Called for pushing input */
	void Push(const FInputActionValue& Value);

	void Forward(const FInputActionValue& Value);

	void ForwardStop(const FInputActionValue & Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPhysicsHandleComponent* GetPhysicsHandleComponent() const { return PhysicsHandle; }

	void SetTraceChannel(int newChannel) { CurrentTraceChannel = newChannel; }

	void ResetTraceChannel() { CurrentTraceChannel = DefaultTraceChannel; }

	int GetTraceChannel() const { return CurrentTraceChannel; }
};

