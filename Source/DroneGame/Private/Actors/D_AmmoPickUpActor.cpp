// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/D_AmmoPickUpActor.h"

#include "Components/SphereComponent.h"
#include "Pawns/D_Drone.h"
#include "Player/D_PlayerState.h"

AD_AmmoPickUpActor::AD_AmmoPickUpActor()
{
	AmmoToAdd = 50.0f;

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AD_AmmoPickUpActor::OnOverlapBegin);
}

void AD_AmmoPickUpActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AD_Drone* Player = Cast<AD_Drone>(OtherActor))
		if (AD_PlayerState* PlayerState = Player->GetPlayerState<AD_PlayerState>())
		{
			PlayerState->AddAmmo(AmmoToAdd);
			Destroy();
		}
}
