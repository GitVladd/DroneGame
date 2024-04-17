#include "CombatComponent.h"

#include "DroneGame/Pawn/BasePawn.h"

#include "DroneGame/Actor/Weapon.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCombatComponent::InitializeComponent()
{
	if (AActor* owner = GetOwner()) {
		BasePawnOwner = Cast<ABasePawn>(owner);
		if (BasePawnOwner) return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s owner was not initialized"), *FString(GetClass()->GetName()));
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCombatComponent::Shoot(const FVector& Direction)
{
	if (IsValid(CurrentWeapon)) {
		CurrentWeapon->Shoot(Direction);
	}
}

