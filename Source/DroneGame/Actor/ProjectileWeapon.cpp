#pragma once

#include "ProjectileWeapon.h"

#include "Kismet/GameplayStatics.h"

#include "DroneGame/Actor/Projectile.h"
#include "DroneGame/Pawn/BasePawn.h"


bool AProjectileWeapon::Shoot(const FVector3d& Direction)
{
	if (!Super::Shoot(Direction)) {
		return false;
	}

	if (!ProjectileClass) {
		UE_LOG(LogTemp, Warning, TEXT("Shoot() failed: ProjectileClass is not defined [Actor: %s]"), *GetName());
		return false;
	}

	UWorld* World = GetWorld();
	if (!World) {
		UE_LOG(LogTemp, Warning, TEXT("Shoot() failed: GetWorld() returned nullptr [Actor: %s]"), *GetName());
		return false;
	}


	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetWeaponOwner();
	SpawnParams.Instigator = Cast<APawn>(GetWeaponOwner());

	FRotator SpawnRotation = Direction.Rotation();
	FVector SpawnLocation = GetTransform().GetLocation();

	AProjectile* newProj = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (!newProj) {
		UE_LOG(LogTemp, Warning, TEXT("InitializeComponent() failed: GetComponentOwner() returned nullptr [Component ID: %s]"), *GetName());
		return false;
	}

	LastShootTime = 0.f;

	if(!bHasUnlimitedAmmo){
		--CurAmmo;
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetWeaponOwner()->GetActorLocation());
	}
	return true;
}
