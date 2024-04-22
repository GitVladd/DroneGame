// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DroneGame/Pawn/BasePawn.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UHealthComponent::InitializeComponent()
{
	Super::InitializeComponent();

	FString ComponentId = GetName();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeComponent() failed: GetComponentOwner() returned nullptr [Component ID: %s]"), *ComponentId);
		return;
	}

	BasePawnOwner = Cast<ABasePawn>(Owner);
	if (!BasePawnOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeComponent() failed: Owner is not of type ABasePawn [Component ID: %s]"), *ComponentId);
		return;
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void  UHealthComponent::SetCurHp(float Value) {
	CurHp = FMath::Clamp(Value, 0.f, MaxHp);

	if (CurHp == 0.f) {
		bIsDead = true;
		OnDeath();
	}
}
float UHealthComponent::GetCurHp() const {
	return CurHp;
}

float  UHealthComponent::GetMaxHp() const {
	return MaxHp;
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

void UHealthComponent::DealDamage(float Value)
{
	if (Value <= 0) return;
	if (bIsDead) return;
	float newHp = CurHp - Value;
	SetCurHp(newHp);
}

void UHealthComponent::Heal(float Value)
{
	if (Value <= 0) return;
	if (bIsDead) return;
	float newHp = CurHp + Value;
	SetCurHp(newHp);
}

void UHealthComponent::OnDeath()
{
	BasePawnOwner->OnDeath();
}

void UHealthComponent::Respawn()
{
	bIsDead = false;
	CurHp = MaxHp;
}
