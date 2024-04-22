// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Consumable.h"

#include "AmmoConsumable.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DRONEGAME_API AAmmoConsumable : public AConsumable
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	int AddAmmoAmount = 100.f;
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
