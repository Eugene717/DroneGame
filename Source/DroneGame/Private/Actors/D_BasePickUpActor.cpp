// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/D_BasePickUpActor.h"

#include "Components/SphereComponent.h"

AD_BasePickUpActor::AD_BasePickUpActor()
{
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->SetupAttachment(RootComponent);
}
