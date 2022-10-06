// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void actorDied(AActor* deadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void startGame();

	UFUNCTION(BlueprintImplementableEvent)
		void gameOver(bool bWonGame);

private:
	class AToonTanksPlayerController* toonTanksPlayerController;

	void handleGameStart();

	float startDelay = 3.f;
	
	int targetTowersCount = 0;

	int getTargetTowerCount();

	
};
