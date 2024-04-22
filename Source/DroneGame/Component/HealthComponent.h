// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class ABasePawn* BasePawnOwner;

protected:
	UPROPERTY(EditAnywhere,  meta = (AllowPrivateAccess = "true"))
	float MaxHp = 100.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CurHp = MaxHp;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;


public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void SetCurHp(float Value);
public:

	UFUNCTION(BlueprintCallable)
	float GetCurHp() const;
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() const;
	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	void DealDamage(float Value);
	void Heal(float Value);
	void OnDeath();
	void Respawn();

public:
		
};
