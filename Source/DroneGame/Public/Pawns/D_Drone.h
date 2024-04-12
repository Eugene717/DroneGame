// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "D_MechaBase.h"
#include "D_Drone.generated.h"

class UFloatingPawnMovement;
class UCameraComponent;

DECLARE_DELEGATE_OneParam(FOnHealthChangedDelegate, float);

UCLASS()
class DRONEGAME_API AD_Drone : public AD_MechaBase
{
	GENERATED_BODY()

public:
	AD_Drone();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Heal();

	void StopMoving();

protected:
	virtual void BeginPlay() override;

public:
	FOnHealthChangedDelegate OnHealthChangedDelegate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UFloatingPawnMovement> PawnMovement;

};
