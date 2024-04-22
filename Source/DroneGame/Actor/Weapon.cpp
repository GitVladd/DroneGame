#pragma once

#include "Weapon.h"

#include "DroneGame/Pawn/BasePawn.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    LastShootTime += DeltaTime;

}

void AWeapon::SetWeaponOwner(ABasePawn* NewOwner)
{
    if (WeaponOwner) {
        FString prevOwnerName = WeaponOwner->GetName();
        FString newOwnerName = NewOwner ? NewOwner->GetName() : TEXT("None");

        UE_LOG(LogTemp, Warning, TEXT("Weapon Owner reinitialization from %s (ID: %d) to %s (ID: %d)"),
            *prevOwnerName, WeaponOwner->GetUniqueID(), *newOwnerName, NewOwner ? NewOwner->GetUniqueID() : -1);
    }
	WeaponOwner = NewOwner;
    SetOwner(WeaponOwner);
}

ABasePawn* AWeapon::GetWeaponOwner() const
{
    return WeaponOwner;
}

bool AWeapon::Shoot()
{
    if (LastShootTime < RateOfFire) {
        return false;
    }
    if (!bHasUnlimitedAmmo && CurAmmo <= 0) {
        return false;
    }
    if (!WeaponOwner) {
        UE_LOG(LogTemp, Warning, TEXT("Shoot() failed: GetWeaponOwner() returned nullptr [Actor: %s]"), *GetName());
        return false;
    }
    return true;
}

bool AWeapon::Shoot(const FVector3d& Direction)
{
    return AWeapon::Shoot();
}

void AWeapon::AddAmmo(int Value)
{
    CurAmmo += Value;
    CurAmmo = FMath::Clamp(CurAmmo, 0.f, MaxAmmo);
}

int AWeapon::GetCurAmmo() const
{
    return CurAmmo;
}

int AWeapon::GetMaxAmmo() const
{
    return MaxAmmo;
}

