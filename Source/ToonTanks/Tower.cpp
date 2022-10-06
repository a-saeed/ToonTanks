// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isTankInFireRange())
	{
		rotateTurret(tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//get hold of the tank object
	tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//initialise the timer manager
	GetWorldTimerManager().SetTimer(fireRateTimerHandle, this, &ATower::checkFireCondition, fireRate, true);
}

void  ATower::handleDestruction()
{
	//call the handleDestruction() from the basePawn to apply visual/sound effects.. then destroy the enemy tower
	Super::handleDestruction();
	Destroy();
}
void ATower::checkFireCondition()
{
	if (tank == nullptr)
	{
		return;
	}
	if (isTankInFireRange() && tank->bAlive )
	{
		fire();
	}

}

bool ATower::isTankInFireRange()
{
	/*
	*get the distance between the enemy tower and the tank
	*if the tank is within fire range
	* we will rotate the tower so that it faces the tank to shoot it
	*/

	if (tank)
	{
		float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());

		return distance <= fireRange;
	}
	return false;
}