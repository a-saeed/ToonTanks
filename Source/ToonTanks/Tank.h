// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	//Tank Constructor
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void handleDestruction();

	APlayerController* getTankPlayerController() { return tankPlayerController; }

	bool bAlive = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "componenets")
		class UCameraComponent* cameraComp;
	UPROPERTY(VisibleAnywhere, Category = "componenets")
		class USpringArmComponent* springArmComp;
	UPROPERTY(EditAnywhere, Category = "movement")
		float speed;
	UPROPERTY(EditAnywhere, Category = "movement")
		float turnRate;
	
	void move(float); //move tank
	void turn(float); //rotate turret

	APlayerController* tankPlayerController;

};
