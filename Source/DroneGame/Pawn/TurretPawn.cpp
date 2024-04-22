#include "TurretPawn.h"

#include "DroneGame/Pawn/DronePawn.h"
#include "DroneGame/Actor/Weapon.h"

#include "Perception/PawnSensingComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

ATurretPawn::ATurretPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ATurretPawn::OnSeeDrone);
	PawnSensingComponent->bHearNoises = false;
	PawnSensingComponent->SetPeripheralVisionAngle(90);
	PawnSensingComponent->SightRadius = 4000;
	PawnSensingComponent->SensingInterval = 0.01;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
	MovementComponent->MaxSpeed = 0.f;
	MovementComponent->Acceleration = 0.f;
	MovementComponent->Deceleration = 0.f;
	MovementComponent->TurningBoost = 1.f;
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurretPawn::OnDeath()
{
	Super::OnDeath();

	Destroy();
}

void ATurretPawn::PointTheWeaponInDirection(FRotator Rotator)
{

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), Rotator, GetWorld()->GetDeltaSeconds(), SmoothRotationSpeed);

	SetActorRotation(NewRotation);
}


void ATurretPawn::OnSeeDrone(APawn* Pawn)
{
	if (ADronePawn* Drone = Cast<ADronePawn>(Pawn))
	{
		if (Drone->GetHealthComponent()->IsDead()) {
			return;
		}
		auto CurWeapon = CombatComponent->GetCurrentWeapon();
		if (!CurWeapon) {
			UE_LOG(LogTemp, Warning, TEXT("OnSeeDrone() failed: CurWeapon is not initialized [Actor ID: %s]"), *GetName());
			return;
		}

		FVector TargetLocation = Drone->GetActorLocation();
		FVector MyLocation = CurWeapon->GetActorLocation();
		FVector Direction = (TargetLocation - MyLocation).GetSafeNormal(); 

		PointTheWeaponInDirection(Direction.Rotation());


		float DotProduct = FVector::DotProduct(GetActorForwardVector(), Direction);
	

		if (DotProduct >= FacingThreshold)
		{
			Shoot(Direction);
		}
	}
}



