#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DroneGame/Pawn/BasePawn.h"

#include "DronePawn.generated.h"

UCLASS(Abstract)
class DRONEGAME_API ADronePawn : public ABasePawn
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

private:
	FVector MovementDirection;
public:
	//Init values for movement component.
	float InitMaxSpeed = 800.f;

	float InitAcceleration = 1000.f;

	float InitDeceleration = 1000.f;

	float InitTurningBoost = 1.f;
public:
	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float RotationSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float MinYawAngle = -80;
	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float MaxYawAngle = 80;
	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float MinPitchAngle = -80;
	UPROPERTY(EditAnywhere, Category = "Camera|Rotation Settings")
	float MaxPitchAngle = 80;

public:
	ADronePawn();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);

	void RotateCamera(FVector2D Value);
};
