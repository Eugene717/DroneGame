// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "D_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AD_PlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		float GetHealth() const;

	UFUNCTION(BlueprintCallable)
		float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
		void AddHealth(float HealthToAdd);

	UFUNCTION(BlueprintCallable)
		int GetAmmoCount() const;

	bool AmmoEmpty() const;

	void AmmoSpent();

	UFUNCTION(BlueprintCallable)
		void AddAmmo(float AmmoToAdd);

protected:
	virtual void BeginPlay() override;

private:
	void OnHealthChanged(const float NewHealth);

protected:
	float Health = 100.0f;
	float MaxHealth = 100.0f;
	int AmmoAmount = 200;
};
