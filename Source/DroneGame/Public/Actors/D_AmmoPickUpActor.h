// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/D_BasePickUpActor.h"
#include "D_AmmoPickUpActor.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AD_AmmoPickUpActor : public AD_BasePickUpActor
{
	GENERATED_BODY()
public:
	AD_AmmoPickUpActor();

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	float AmmoToAdd;

};
