#pragma once

#include "ProjectileWeapon.h"

#include "DroneGame/Actor/Projectile.h"

void AProjectileWeapon::Shoot(const FVector& Direction) {
	Super::Shoot(Direction);

	if (!ProjectileClass) return;


}
