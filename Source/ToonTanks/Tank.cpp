// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
	//initialise tank components and set their attacments
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("arm"));
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	cameraComp->SetupAttachment(springArmComp);
}

void ATank::handleDestruction()
{
	//call the handleDestruction() from the basePawn to apply visual/sound effects.. then hide the tank and disable its tick function
	Super::handleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::turn);

	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (tankPlayerController)
	{
	//each frame, we want to get the hit result based on our cursor movement 
	FHitResult hitResult;
	tankPlayerController -> GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
/*
	//then draw  debug sphere every single frame, that gets erased after..
		DrawDebugSphere(GetWorld(),
			hitResult.ImpactPoint,
			20,
			12,
			FColor::Red,
			false,
			-1.0f);
*/

		/*
		* call the rotate turret method implemented in basePawn class that we created
		*/
		rotateTurret(hitResult.ImpactPoint);
	}

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	tankPlayerController = Cast<APlayerController>(GetController());
}


void ATank::move(float vlaue)
{
	FVector deltaLocation(0.f); // initialize the vector with zero values.. another way to do it ->>> = FVector::ZeroVector; 
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	deltaLocation.X = vlaue * speed * deltaTime;

	//call the fuction that moves the pawn accorging to its local position
	AddActorLocalOffset(deltaLocation, true);
}

void ATank::turn(float value)
{
	FRotator deltaRotator = FRotator::ZeroRotator;
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	deltaRotator.Yaw = value * turnRate * deltaTime; //Yaw is responsible for rotation of an object around the z axis, which is what we want for ouy turret.
	AddActorLocalRotation(deltaRotator, true);
}
