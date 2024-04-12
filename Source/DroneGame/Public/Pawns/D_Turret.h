// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "D_MechaBase.h"
#include "D_Turret.generated.h"

UCLASS()
class DRONEGAME_API AD_Turret : public AD_MechaBase
{
	GENERATED_BODY()

public:
	AD_Turret();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FVector GetTowerLocation() const;

	FRotator GetTowerRotation() const;

	void Rotate();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> TowerMeshComponent;

};
