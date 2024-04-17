#pragma once

#include "BasePawn.h"

#include "DroneGame/Component/HealthComponent.h"
#include "DroneGame/Component/CombatComponent.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SetRootComponent(SkeletalMesh);

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


float ABasePawn::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageTaken <= 0) return 0.f;
	float newHp = HealthComponent->GetCurHp() - DamageTaken;
	HealthComponent->SetCurHp(newHp);
	HealthComponent->IsDead();
	
	return DamageTaken;
}

const UHealthComponent* ABasePawn::GetHealthComponent() const
{
	return HealthComponent;
}

const UCombatComponent* ABasePawn::GetCombatComponent() const
{
	return CombatComponent;
}

void ABasePawn::Shoot(const FVector& Direction)
{
	if (IsValid(CombatComponent)) {
		CombatComponent->Shoot(Direction);
	}
}

void ABasePawn::OnDeath()
{
}

