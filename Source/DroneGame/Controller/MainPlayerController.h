#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MainPlayerController.generated.h"

UCLASS()
class DRONEGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class ADronePawn* ControlledDronePawn;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CameraZoomInputAction;
protected:

	virtual void BeginPlay();

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

protected:
	virtual void OnMoveInputActionTriggered(const struct FInputActionValue& Value);
	virtual void OnRotateInputActionTriggered(const struct FInputActionValue& Value);

};
