// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//handle destruction for the tower
	void handleDestruction();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	class ATank* tank;

	UPROPERTY(EditAnywhere,Category = "combat")
		float fireRange;
	
	FTimerHandle fireRateTimerHandle;
	float fireRate = 2.f;

	void checkFireCondition();

	bool isTankInFireRange();
};
