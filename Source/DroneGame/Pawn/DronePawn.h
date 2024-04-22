#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DroneGame/Pawn/BasePawn.h"

#include "DronePawn.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ADronePawn : public ABasePawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

public:
	float InitMaxSpeed = 800.f;

	float InitAcceleration = 1000.f;

	float InitDeceleration = 1000.f;

	float InitTurningBoost = 1.f;

	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float RotationSpeed = 90.f;

	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float SmoothRotationSpeed = 10.f;

public:
	ADronePawn();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	class UCameraComponent* GetCameraComponent() const;

public:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);

	void RotateCamera(FVector2D Value);
	void RotateDrone(FVector2D Value);

	virtual void OnDeath() override;
};
