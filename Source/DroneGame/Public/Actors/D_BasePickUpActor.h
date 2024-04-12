// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "D_BasePickUpActor.generated.h"

class USphereComponent;

UCLASS(Abstract)
class DRONEGAME_API AD_BasePickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AD_BasePickUpActor();

protected:

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) PURE_VIRTUAL(AD_BasePickUpActor::OnOverlapBegin);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		TObjectPtr<USphereComponent> SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
		TObjectPtr<UStaticMeshComponent> ActorMesh;

};
