// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/D_MechaBase.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Projectiles/D_BaseProjectile.h"

AD_MechaBase::AD_MechaBase()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	ProjectileBasePosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnComponent"));
	ProjectileBasePosition->SetupAttachment(MeshComponent);
}

void AD_MechaBase::Fire()
{
	UWorld* World = GetWorld();

	World->SpawnActor<AD_BaseProjectile>(Bullet, ProjectileBasePosition->GetComponentLocation(), ProjectileBasePosition->GetComponentRotation());
}

void AD_MechaBase::BeginPlay()
{
	Super::BeginPlay();
	
}

