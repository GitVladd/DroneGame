#pragma once

#include "CoreMinimal.h"

#include "Weapon.h"

#include "ProjectileWeapon.generated.h"

UCLASS(Abstract)
class DRONEGAME_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = ( AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

public:
	virtual bool Shoot(const FVector3d& Direction) override;


};
