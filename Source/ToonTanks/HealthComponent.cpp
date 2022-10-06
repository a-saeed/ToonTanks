// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	health = maxHealth;

	/*
	* bind the damage taken callback to the onTakeAnyDamage delegate (event)
	* this event is only accessible to actor class
	* so we need to get the owner that contains this health component
	*/
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::damageTaken);
	
	//get hold of the game mode so we can call its actorDies function.
	toonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::damageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* damageCausor)
{
	if (health <= 1 && toonTanksGameMode)
	{
		toonTanksGameMode->actorDied(damagedActor);
	}
	health -= damage;

	UE_LOG(LogTemp, Warning, TEXT("Health:: %f"), health);
}
