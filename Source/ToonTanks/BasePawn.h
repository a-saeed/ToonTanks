// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//handle destruction function
	void handleDestruction();

protected:
	void rotateTurret(FVector);
	void fire();

private:
	//forward declare UCapsuleComponent
	UPROPERTY(VisibleAnywhere, Category = "components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		class UCapsuleComponent* capsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere, Category = "components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere, Category = "components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "combat")
		TSubclassOf<class AProjectile> BP_projectileClass;

	UPROPERTY(EditAnywhere, Category = "combat")
		UParticleSystem* deathParticle;

	UPROPERTY(EditAnywhere, Category = "combat")
		class USoundBase* deathSound;

	UPROPERTY(EditAnywhere, Category = "combat")
		TSubclassOf<UCameraShakeBase> deathCameraShakeClass;
};
