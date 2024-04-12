// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "D_PlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class DRONEGAME_API AD_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AD_PlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void Move(const FInputActionValue& InputActionValue);
	void MoveUpDown(const FInputActionValue& InputActionValue);
	void Rotate(const FInputActionValue& InputActionValue);
	void Fire(const FInputActionValue& InputActionValue);

private:
	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputMappingContext> DroneGameContext;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> MoveUpDownAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
		TObjectPtr<UInputAction> FireAction;

};
