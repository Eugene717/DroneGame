// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/D_PlayerState.h"

#include "Pawns/D_Drone.h"

void AD_PlayerState::BeginPlay()
{
	Super::BeginPlay();
		
	if (AD_Drone* PlayerPawn = GetPawn<AD_Drone>())
	{
		PlayerPawn->OnHealthChangedDelegate.BindUObject(this, &AD_PlayerState::OnHealthChanged);
	}
}

float AD_PlayerState::GetHealth() const
{
	return Health;
}

float AD_PlayerState::GetMaxHealth() const
{
	return MaxHealth;
}

void AD_PlayerState::AddHealth(float HealthToAdd)
{
	Health += FMath::Clamp(HealthToAdd, 0.0f, MaxHealth);

	if (AD_Drone* PlayerPawn = GetPawn<AD_Drone>())
	{
		PlayerPawn->Heal();
	}
}

void AD_PlayerState::AddAmmo(float AmmoToAdd)
{
	AmmoAmount += AmmoToAdd;
}

int AD_PlayerState::GetAmmoCount() const
{
	return AmmoAmount;
}

void AD_PlayerState::OnHealthChanged(const float NewHealth)
{
	Health = NewHealth;
}

bool AD_PlayerState::AmmoEmpty() const
{
	return AmmoAmount == 0;
}

void AD_PlayerState::AmmoSpent()
{
	--AmmoAmount;
}

