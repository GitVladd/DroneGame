#include "MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"

#include "DroneGame/Pawn/DronePawn.h"


void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnMoveInputActionTriggered);

		EnhancedInputComponent->BindAction(RotateInputAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnRotateInputActionTriggered);

		EnhancedInputComponent->BindAction(CameraLockInputAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnCameraLockInputActionTriggered);

		EnhancedInputComponent->BindAction(CameraLockInputAction, ETriggerEvent::Completed, this, &AMainPlayerController::OnCameraLockInputActionCompleted);

		EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnShootInputActionTriggered);

		EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Ongoing, this, &AMainPlayerController::OnShootInputActionOngoing);
	}
}



void AMainPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControlledDronePawn = CastChecked<ADronePawn>(GetPawn());
}

void AMainPlayerController::OnMoveInputActionTriggered(const FInputActionValue& Value)
{
	auto DirectionVector = Value.Get<FVector>();
	if (ControlledDronePawn) {
		ControlledDronePawn->MoveForward(DirectionVector.Y);
		ControlledDronePawn->MoveRight(DirectionVector.X);
		ControlledDronePawn->MoveUp(DirectionVector.Z);
	}
}

void AMainPlayerController::OnRotateInputActionTriggered(const FInputActionValue& Value)
{
	if (ControlledDronePawn) {
		if (!bIsCameraLocked) {
			ControlledDronePawn->RotateCamera(Value.Get<FVector2D>());
			return;
		}
		else {
			ControlledDronePawn->RotateDrone(Value.Get<FVector2D>());
			return;
		}
	}
}

void AMainPlayerController::OnCameraLockInputActionTriggered(const FInputActionValue& Value)
{
	bIsCameraLocked = true;
}

void AMainPlayerController::OnCameraLockInputActionCompleted(const FInputActionValue& Value)
{
	bIsCameraLocked = false;
}

void AMainPlayerController::OnShootInputActionTriggered(const FInputActionValue& Value)
{
	if (ControlledDronePawn) {
		const FRotator SpawnRotation = PlayerCameraManager->GetCameraRotation();
		FVector3d Direction = SpawnRotation.Vector();
		ControlledDronePawn->Shoot(Direction);
	}
}

void AMainPlayerController::OnShootInputActionOngoing(const FInputActionValue& Value)
{
	if (ControlledDronePawn) {
		const FRotator SpawnRotation = PlayerCameraManager->GetCameraRotation();
		FVector3d Direction = SpawnRotation.Vector();
		ControlledDronePawn->Shoot(Direction);
	}
}
