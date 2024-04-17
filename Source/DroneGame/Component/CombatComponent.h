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

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;
public:	
	UCombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void Shoot(const FVector& Direction);
		
};
