// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "movement")
		class UProjectileMovementComponent* movementComp;

	UPROPERTY(VisibleAnywhere, Category = "combat")
		class UParticleSystemComponent* trailParticle;

	//this is a callback function (event to be more precise) that will be bound to a hit event for this object.. the function gets called every time the projectile hits or is hit by other objects in the world 
	UFUNCTION()
		void onHit(UPrimitiveComponent* hitComp, AActor* otherActor , UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hitResult);
	
	UPROPERTY(EditAnywhere)
		float damageAmount = 25.f;

	UPROPERTY(EditAnywhere, Category = "combat")
		UParticleSystem* hitParticle;

	UPROPERTY(EditAnywhere, Category = "combat")
		class USoundBase* launchSound;

	UPROPERTY(EditAnywhere, Category = "combat")
		USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category = "combat")
		TSubclassOf<UCameraShakeBase> hitCameraShakeClass;
};
