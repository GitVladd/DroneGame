// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DroneGame/Component/CombatComponent.h"
#include "DroneGame/Component/HealthComponent.h"

#include "BasePawn.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;
public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	const UHealthComponent* GetHealthComponent() const;

	const UCombatComponent* GetCombatComponent() const;

public:
	void Shoot(const FVector& Direction);

protected:
	virtual void OnDeath();
};
