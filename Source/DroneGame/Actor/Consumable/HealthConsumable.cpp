// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthConsumable.h"

#include "Kismet/GameplayStatics.h"

#include "DroneGame/Pawn/DronePawn.h"

void AHealthConsumable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		ADronePawn* HitPawn = Cast<ADronePawn>(OtherActor);
		if (HitPawn) {
			HitPawn->GetHealthComponent()->Heal(HealAmount);

			if (PickUpSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
			}
			Destroy();
		}
	}
}