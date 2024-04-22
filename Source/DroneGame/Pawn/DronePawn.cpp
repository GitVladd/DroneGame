
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
	CameraComponent->bUsePawnControlRotation = true;

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


UCameraComponent* ADronePawn::GetCameraComponent() const
{
	return CameraComponent;
}

void ADronePawn::MoveForward(float Value)
{
	FVector3d Direction = GetActorForwardVector() * Value;

	MovementComponent->AddInputVector(Direction);
}

void ADronePawn::MoveRight(float Value)
{
	FVector3d Direction = GetActorRightVector() * Value;

	MovementComponent->AddInputVector(Direction);
}

void ADronePawn::MoveUp(float Value)
{
	FVector3d Direction = GetActorUpVector() * Value;

	MovementComponent->AddInputVector(Direction);
}

void ADronePawn::RotateCamera(FVector2D Value)
{
	if (!CameraComponent) return;
	if (!Controller) return;

	float AdjustedRotationSpeed = RotationSpeed * GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(Value.X * AdjustedRotationSpeed);
	AddControllerPitchInput(Value.Y * AdjustedRotationSpeed);
}

void ADronePawn::RotateDrone(FVector2D Value)
{
	if (!CameraComponent) return;
	if (!Controller) return;

	float AdjustedRotationSpeed = RotationSpeed * GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(Value.X * AdjustedRotationSpeed);
	AddControllerPitchInput(Value.Y * AdjustedRotationSpeed);

	FRotator ControlRotation = GetControlRotation();
	FRotator TargetRotation = FRotator(0.f, ControlRotation.Yaw, 0.f); 
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), SmoothRotationSpeed);

	MovementComponent->UpdatedComponent->SetWorldRotation(NewRotation);

}

void ADronePawn::OnDeath()
{
	Super::OnDeath();

	// Disable the movement component
	if (MovementComponent)
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->Deactivate();
	}

	DisableInput(Cast<APlayerController>(GetController()));

	// Hide the skeletal mesh
	if (SkeletalMesh)
	{
		SkeletalMesh->SetVisibility(false);
	}

}

