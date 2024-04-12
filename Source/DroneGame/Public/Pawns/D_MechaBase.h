// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "D_MechaBase.generated.h"

class UBoxComponent;
class UWidgetComponent;
class AD_BaseProjectile;

UCLASS()
class DRONEGAME_API AD_MechaBase : public APawn
{
	GENERATED_BODY()

public:
	AD_MechaBase();

	void Fire();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
		TObjectPtr<USceneComponent> ProjectileBasePosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Projectile)
		TSubclassOf<AD_BaseProjectile> Bullet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn Class Deafults")
	float Health;
};
