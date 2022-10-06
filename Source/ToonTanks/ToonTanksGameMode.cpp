// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::actorDied(AActor* deadActor)
{

	//if the dead actor is the tank
	if (ATank* tank = Cast<ATank>(deadActor))
	{
		//1-call the handleDestruction function
			//2-disable tank input
			//3-disable cursor
		tank->handleDestruction();

		gameOver(false);

		if (toonTanksPlayerController)
		{
			toonTanksPlayerController->setPlayerEnabledState(false);
		}
	}
	//esle if the dead actor is the tower
	else if (ATower* tower = Cast<ATower>(deadActor))
	{
		//call its handle destruction function
		tower->handleDestruction();
		targetTowersCount--;

		if (targetTowersCount == 0)
		{
			gameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	handleGameStart();
}

void AToonTanksGameMode::handleGameStart()
{
	//get count of enemy towers at beginPlay
	targetTowersCount = getTargetTowerCount();

	//this function is called in begin play
	toonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	//this function is implemented in widget bluperints
	startGame();

	if (toonTanksPlayerController)
	{
		//delay the start of the game

		//we wiil disable the player input for 3 seconds after game starts
		toonTanksPlayerController->setPlayerEnabledState(false);

		//we pass true as the third param to the setPlayerEnabled callback in toonTanksPlayerController to re enable the player input...
		FTimerHandle playerEnabletimerHandle;

		FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(
			toonTanksPlayerController,
			&AToonTanksPlayerController::setPlayerEnabledState,
			true);
		
		//actully set the timre manager
		GetWorldTimerManager().SetTimer(
			playerEnabletimerHandle,
			timerDelegate,
			startDelay,
			false);

	}
}

int AToonTanksGameMode::getTargetTowerCount()
{
	TArray<AActor*> targetTowerArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), targetTowerArray);

	return targetTowerArray.Num();
}
