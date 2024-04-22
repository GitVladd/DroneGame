// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DroneGame/Pawn/BasePawn.h"

#include "TurretPawn.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;

public:
	UPROPERTY(EditAnywhere)
	float SmoothRotationSpeed = 100.f;
	UPROPERTY(EditAnywhere)
	float FacingThreshold = 0.999f;
public:
	ATurretPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void OnDeath() override;

	void PointTheWeaponInDirection(FRotator Rotator);


private:	
	UFUNCTION()
	void OnSeeDrone(APawn* Pawn);
};
