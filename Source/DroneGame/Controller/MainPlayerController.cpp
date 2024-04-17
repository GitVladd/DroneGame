#include "MainPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

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
		ControlledDronePawn->RotateCamera(Value.Get<FVector2D>());
	}
}
