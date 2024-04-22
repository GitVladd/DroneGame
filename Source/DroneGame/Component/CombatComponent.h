#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ABasePawn* BasePawnOwner;


	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AWeapon> CurrentWeaponClass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;
public:
	UPROPERTY(EditDefaultsOnly)
	FName AttachWeaponSocketName = "ShootingLocation";
public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void CreateWeapon();
public:
	virtual void Shoot();
	virtual void Shoot(const FVector3d& Direction);
	UFUNCTION(BlueprintCallable)
	AWeapon* GetCurrentWeapon() const;

};
