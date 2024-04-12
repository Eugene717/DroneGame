// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "D_AIController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class DRONEGAME_API AD_AIController : public AAIController
{
	GENERATED_BODY()
public:
	AD_AIController();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPerception(AActor* Actor, FAIStimulus Stimulus);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	void InitializePerception();

	void RotateToEnemy();

	void Fire();

protected:
	UPROPERTY(VisibleAnywhere)
		TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	TObjectPtr<UAISenseConfig_Sight> SightConfig;

private:
	float ShootTime;

};
