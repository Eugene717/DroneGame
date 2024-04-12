// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D_BaseProjectile.generated.h"

class USphereComponent;

UCLASS()
class DRONEGAME_API AD_BaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AD_BaseProjectile();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		TObjectPtr<UStaticMeshComponent> BulletMesh;

	UPROPERTY(EditAnywhere, Category = BulletSettings)
		float DmgAmount;

	UPROPERTY(EditDefaultsOnly, Category = BulletSettings)
		float BulletSpeed;

};
