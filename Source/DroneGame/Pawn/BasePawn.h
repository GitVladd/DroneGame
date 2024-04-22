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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCombatComponent* CombatComponent;
public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnDeath();
public:
	USkeletalMeshComponent* GetSkeletalMeshComponent() const;

	UHealthComponent* GetHealthComponent() const;

	UCombatComponent* GetCombatComponent() const;

public:
	void Shoot();
	void Shoot(const FVector3d& Direction);
};
