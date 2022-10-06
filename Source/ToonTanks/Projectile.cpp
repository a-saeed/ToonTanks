// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//construct the static mesh component and make it the root component
	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("projectile"));
	RootComponent = projectileMesh;

	//construct the projectile movement component which will be responsible for the movement of the projectile.. duh...
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movement comp"));
	movementComp->MaxSpeed = 3000.f;
	movementComp->InitialSpeed = 1000.f;

	//construct the hit trail particle system component and attach it to the root
	trailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("trail particle"));
	trailParticle->SetupAttachment(projectileMesh);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//actually bind our on hit callback to the invocation list for this event
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::onHit);

	//at beginPlay when a projectile is just fired play the hit Sound
	if (launchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, launchSound, GetActorLocation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::onHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hitResult)
{
	/* this is the information we need to pass to apply damage function*/
	AActor* myOwner = GetOwner(); //return an actor pointer

	if (myOwner == nullptr)
	{
		Destroy(); //the projectile
		return;
	}

	AController* myOwnerInstigator = myOwner->GetInstigatorController();
	UClass* damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != myOwner)
	{
		/*
		* when this function is called it will generate a damage event
		* which will be caught by the OnTakeAnyDamage delegate in healthComponent.cpp
		* which in turn will broadcast this event to any callback attached to it
		* in our case will be damageTaken() callback
		*/
		UGameplayStatics::ApplyDamage(otherActor, damageAmount, myOwnerInstigator, this, damageTypeClass);
		
		//spawn the hit particle system
		if (hitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetActorLocation(), GetActorRotation());
		}
		if (hitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());
		}
		if (hitCameraShakeClass)
		{
			//we need the player controller in order to play the camera shake function
			//we can get it from UWorld
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
		}
	}
	Destroy();
}