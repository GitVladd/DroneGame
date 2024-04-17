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
	UPROPERTY(EditDefaultsOnly,  meta = (AllowPrivateAccess = "true"))
	float MaxHp = 100.f;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CurHp = MaxHp;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;


public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void SetCurHp(float Value);
	float GetCurHp() const;
	float GetMaxHp() const;
	bool IsDead() const;

	void Respawn();

public:
		
};
