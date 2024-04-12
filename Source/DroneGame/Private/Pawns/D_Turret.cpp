// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/D_Turret.h"

AD_Turret::AD_Turret()
{
	TowerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMeshComponent"));
	TowerMeshComponent->SetupAttachment(MeshComponent);

	ProjectileBasePosition->SetupAttachment(TowerMeshComponent);

	Health = 250.0f;
}

void AD_Turret::BeginPlay()
{
	Super::BeginPlay();	
}

float AD_Turret::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageAmount;

	if (Health > 0)
		return DamageAmount;

	Destroy();

	return DamageAmount;
}

FVector AD_Turret::GetTowerLocation() const
{	
	FVector ComponentLocation = TowerMeshComponent->GetComponentLocation();
	ComponentLocation.Z += 60.0f;

	return ComponentLocation;
}

FRotator AD_Turret::GetTowerRotation() const
{
	return TowerMeshComponent->GetComponentRotation();
}

void AD_Turret::Rotate()
{
	FRotator TowerRotation = TowerMeshComponent->GetRelativeRotation();

	FRotator Rotation = GetControlRotation() - GetActorRotation();

	float YawDelta = Rotation.Yaw - TowerRotation.Roll;
	float PitchDelta = Rotation.Pitch - TowerRotation.Roll;

	FRotator NewTowerRotation = FRotator(PitchDelta, YawDelta, 0);

	TowerMeshComponent->SetRelativeRotation(FMath::Lerp(TowerRotation, NewTowerRotation, 0.1));
}


