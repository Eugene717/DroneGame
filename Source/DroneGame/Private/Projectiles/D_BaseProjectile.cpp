// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/D_BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

AD_BaseProjectile::AD_BaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereCollider);

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);

	SphereCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereCollider->OnComponentHit.AddDynamic(this, &AD_BaseProjectile::OnHit);

	DmgAmount = 25.0f;
	BulletSpeed = 20.0f;
}

void AD_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	constexpr float TimeToLive = 3.0f;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, TimeToLive]()
		{
			if (!IsValid(this))
			{
				GetWorldTimerManager().ClearAllTimersForObject(this);
				return;
			}

			float Lifetime = GetWorld()->GetTimeSeconds() - CreationTime;

			if (Lifetime > TimeToLive)
			{
				this->Destroy();
				GetWorldTimerManager().ClearAllTimersForObject(this);
			}
		}, TimeToLive, false);
}

void AD_BaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(BulletSpeed * FVector(1.0f, 0.0f, 0.0f), true);
}

void AD_BaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		float Damage = FMath::FRandRange(DmgAmount - 5, DmgAmount + 5);
		OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
	}

	Destroy();
}


