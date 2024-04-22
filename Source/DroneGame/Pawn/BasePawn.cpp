#pragma once

#include "BasePawn.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "DroneGame/Component/HealthComponent.h"
#include "DroneGame/Component/CombatComponent.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(SkeletalMesh);
	SkeletalMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	SkeletalMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore); 
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	SkeletalMesh->SetGenerateOverlapEvents(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));


	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));

}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float ABasePawn::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageTaken <= 0) return 0.f;

	HealthComponent->DealDamage(DamageTaken);

	return DamageTaken;
}

USkeletalMeshComponent* ABasePawn::GetSkeletalMeshComponent() const
{
	return SkeletalMesh;
}

UHealthComponent* ABasePawn::GetHealthComponent() const
{
	return HealthComponent;
}
UCombatComponent* ABasePawn::GetCombatComponent() const
{
	return CombatComponent;
}


void ABasePawn::Shoot()
{
	if (IsValid(CombatComponent)) {
		CombatComponent->Shoot();
	}
}

void ABasePawn::Shoot(const FVector3d& Direction)
{
	if (IsValid(CombatComponent)) {
		CombatComponent->Shoot(Direction);
	}
}

void ABasePawn::OnDeath()
{
}

