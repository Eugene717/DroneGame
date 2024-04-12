// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/D_Drone.h"

#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Player/D_PlayerState.h"

AD_Drone::AD_Drone()
{
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("PawnMovement"));
	PawnMovement->UpdatedComponent = RootComponent;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;

	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void AD_Drone::BeginPlay()
{
	Super::BeginPlay();

	const AD_PlayerState* DronePlayerState = GetPlayerState<AD_PlayerState>();

	Health = DronePlayerState->GetHealth();
}

float AD_Drone::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageAmount;
	OnHealthChangedDelegate.Execute(Health);

	if (Health > 0)
		return DamageAmount;

	Destroy();

	return DamageAmount;
}

void AD_Drone::Heal()
{
	const AD_PlayerState* DronePlayerState = GetPlayerState<AD_PlayerState>();

	Health = DronePlayerState->GetHealth();
}

void AD_Drone::StopMoving()
{
	PawnMovement->StopMovementImmediately();
}

