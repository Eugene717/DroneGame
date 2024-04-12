// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyLogic/D_AIController.h"

#include "Pawns/D_Drone.h"
#include "Pawns/D_Turret.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AD_AIController::AD_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	InitializePerception();
}

void AD_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!GetFocusActor())
		return;

	RotateToEnemy();
	Fire();
}

void AD_AIController::OnPerception(AActor* Actor, FAIStimulus Stimulus)
{
	AD_Drone* Enemy = Cast<AD_Drone>(Actor);

	if (!Enemy)
		return;

	if (Stimulus.WasSuccessfullySensed())
	{
		SetFocus(Enemy);
		ShootTime = 0.0f;
	}
	else
	{
		SetFocus(nullptr);
	}
}

void AD_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AD_AIController::OnPerception);
}

void AD_AIController::InitializePerception()
{
	AIPerceptionComponent = GetPerceptionComponent();

	if (!AIPerceptionComponent)
		AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig->SightRadius = 4000.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 500.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AD_AIController::RotateToEnemy()
{
	AD_Turret* Turret = Cast<AD_Turret>(GetPawn());

	FVector DirectionToTarget = GetFocusActor()->GetActorLocation() - Turret->GetTowerLocation();

	FRotator RotatorToTarget = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();

	SetControlRotation(RotatorToTarget);

	Turret->Rotate();
}

void AD_AIController::Fire()
{
	AD_Turret* Turret = Cast<AD_Turret>(GetPawn());

	FVector StartPosition = Turret->GetTowerLocation();
	FVector EndPosition = StartPosition + Turret->GetTowerRotation().Vector() * SightConfig->LoseSightRadius;

	FCollisionQueryParams ColParams;
	ColParams.AddIgnoredActor(Turret);

	FHitResult HitResult;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_Pawn, ColParams, FCollisionResponseParams()))
	{
		AActor* HitActor = HitResult.GetActor();

		if (GetFocusActor() == HitActor)
		{
			ShootTime -= GetWorld()->GetDeltaSeconds();

			if (ShootTime <= 0.0f)
			{
				for (int i = FMath::FRandRange(1.0f, 3.5f); i > 0; --i)
					Turret->Fire();

				ShootTime = 1.0f;
			}
		}
	}
}
