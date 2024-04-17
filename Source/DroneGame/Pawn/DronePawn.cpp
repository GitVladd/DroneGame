
#include "DronePawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ADronePawn::ADronePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = -10.f;
	SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
	MovementComponent->MaxSpeed = InitMaxSpeed;
	MovementComponent->Acceleration = InitAcceleration;
	MovementComponent->Deceleration = InitDeceleration;
	MovementComponent->TurningBoost = InitTurningBoost;

}

void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ADronePawn::MoveForward(float Value)
{
	MovementDirection.X = Value;
	//MovementDirection.Normalize();
	MovementComponent->AddInputVector(MovementDirection);
}

void ADronePawn::MoveRight(float Value)
{
	MovementDirection.Y = Value;
	//MovementDirection.Normalize();
	MovementComponent->AddInputVector(MovementDirection);
}

void ADronePawn::MoveUp(float Value)
{
	MovementDirection.Z = Value;
	//MovementDirection.Normalize();
	MovementComponent->AddInputVector(MovementDirection);
}

// TO DO : FIX CAMERA ROTAITON
void ADronePawn::RotateCamera(FVector2D Value)
{
	if (!CameraComponent) return;

	// Calculate the delta rotation based on input values
	FVector Axis = FVector(0.0f, 0.0f, 1.0f); // Rotation axis is around Z-axis for yaw
	FRotator DeltaRotation = FRotator(-Value.Y * RotationSpeed, Value.X * RotationSpeed, 0.0f);

	// Convert the delta rotation to a quaternion
	FQuat DeltaQuat = FQuat(DeltaRotation);

	// Get the current relative rotation of the camera as a quaternion
	FQuat CurrentQuat = FQuat(CameraComponent->GetRelativeRotation());

	// Combine the delta rotation with the current rotation using quaternion multiplication
	FQuat NewQuat = CurrentQuat * DeltaQuat;

	// Normalize the resulting quaternion to ensure it represents a valid rotation
	NewQuat.Normalize();

	// Convert the resulting quaternion back to a rotator
	FRotator NewRotation = NewQuat.Rotator();

	// Set the new relative rotation of the camera
	CameraComponent->SetRelativeRotation(NewRotation);
}

