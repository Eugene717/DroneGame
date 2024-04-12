// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/D_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Pawns/D_MechaBase.h"
#include "Player/D_PlayerState.h"
#include "Projectiles/D_BaseProjectile.h"

AD_PlayerController::AD_PlayerController()
{	
}

void AD_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DroneGameContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(DroneGameContext, 0);
}

void AD_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AD_PlayerController::Move);
	EnhancedInputComponent->BindAction(MoveUpDownAction, ETriggerEvent::Triggered, this, &AD_PlayerController::MoveUpDown);
	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AD_PlayerController::Rotate);
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AD_PlayerController::Fire);
}

void AD_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AD_PlayerController::MoveUpDown(const FInputActionValue& InputActionValue)
{
	const float InputAxisFloat = InputActionValue.Get<float>();

	const FVector Direction = FVector::UpVector * InputAxisFloat;

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{

		ControlledPawn->AddMovementInput(Direction);
	}
}

void AD_PlayerController::Rotate(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	float YawRotation = 0.0f;
	float PitchRotation = 0.0f;

	constexpr float RotationSpeed = 100.0f;

	YawRotation += InputAxisVector.X * RotationSpeed * GetWorld()->GetDeltaSeconds();
	PitchRotation += InputAxisVector.Y * RotationSpeed * GetWorld()->GetDeltaSeconds();

	RotationInput.Add(PitchRotation, YawRotation, 0.0f);
}

void AD_PlayerController::Fire(const FInputActionValue& InputActionValue)
{
	AD_PlayerState* DronePlayerState = Cast<AD_PlayerState>(PlayerState);

	if (DronePlayerState->AmmoEmpty())
		return;

	GetPawn<AD_MechaBase>()->Fire();
	DronePlayerState->AmmoSpent();
}

