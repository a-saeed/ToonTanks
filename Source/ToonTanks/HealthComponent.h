// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
		float maxHealth = 100.f;

	float health;

	class AToonTanksGameMode* toonTanksGameMode;

	//this function will be bound to take damage event so it has to take the right input parameters..
	UFUNCTION() //--> we have to write this line for without it, we can't bind the callback with the damage event(or any event for that matter)..
		void damageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* damageCausor);
	
};
