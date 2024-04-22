#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Abstract)
class DRONEGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class ABasePawn* WeaponOwner;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RateOfFire = 0.1f;
	UPROPERTY(VisibleAnywhere, Category = Gameplay, meta = (AllowPrivateAccess = true))
	float LastShootTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MaxAmmo = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int CurAmmo = MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	bool bHasUnlimitedAmmo = false;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay, meta = (AllowPrivateAccess = true))
	USoundBase* FireSound;

public:	
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetWeaponOwner(class ABasePawn* Owner);
	ABasePawn* GetWeaponOwner() const;
	virtual bool Shoot();
	virtual bool Shoot(const FVector3d& Direction);
	void AddAmmo(int Value);

	UFUNCTION(BlueprintCallable)
	int GetCurAmmo() const;
	UFUNCTION(BlueprintCallable)
	int GetMaxAmmo() const;
};
