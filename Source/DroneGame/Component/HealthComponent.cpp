// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "DroneGame/Pawn/BasePawn.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UHealthComponent::InitializeComponent()
{
	if (AActor* owner = GetOwner()) {
		BasePawnOwner = Cast<ABasePawn>(owner);
		if (BasePawnOwner) return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s owner was not initialized"), *FString(GetClass()->GetName()));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void  UHealthComponent::SetCurHp(float Value) {
	CurHp = FMath::Clamp(Value, 0.f, MaxHp);

	if (CurHp == 0.f) {
		bIsDead = true;
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

void UHealthComponent::Respawn()
{
	bIsDead = false;
	CurHp = MaxHp;
}
