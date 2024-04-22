// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AmmoConsumable.h"

#include "Kismet/GameplayStatics.h"

#include "DroneGame/Pawn/DronePawn.h"
#include "DroneGame/Actor/Weapon.h"

void AAmmoConsumable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this)
	{
		ADronePawn* HitPawn = Cast<ADronePawn>(OtherActor);
		if (HitPawn) {
			HitPawn->GetCombatComponent()->GetCurrentWeapon()->AddAmmo(AddAmmoAmount);
			if (PickUpSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
			}
			Destroy();
		}
	}
}