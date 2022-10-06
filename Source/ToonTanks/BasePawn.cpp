#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComp = CreateDefaultSubobject<UCapsuleComponent> (TEXT("capsule collider")); //create a capsule component in this base class from which we will derive other pawns..

	RootComponent = capsuleComp; //then make it the root component

	/*create some static mesh / scene comps and setup their attachments*/
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("base mesh"));
	baseMesh->SetupAttachment(capsuleComp);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("turret mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("spawn point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);


}

void ABasePawn::handleDestruction()
{
	//handle visual/sound effects
	if (deathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, deathParticle, GetActorLocation(), GetActorRotation());
	}
	if (deathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());
	}
	if (deathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
	}
}

void ABasePawn::rotateTurret(FVector targetPoint)
{
	/*the idea is to get the vector(toTarget) that starts from the turret meshand ends at the point where the cursor is at..
	* then rotate the turret mesh based on that vector..
	* but we don't want the turret to rotate around except the z-axis (the yaw component of the rotation)
	* so we zero out all other rotation axes.
	* vector math --> toTarget = target point - start point
	* last step is to actually set the rotation of the turret
	*/

	FVector toTarget = targetPoint - turretMesh->GetComponentLocation();
	FRotator lookAtRotation = FRotator(0.f, toTarget.Rotation().Yaw , 0.f);

	turretMesh->SetWorldRotation(
		FMath::RInterpTo(
			turretMesh->GetComponentRotation(),
			lookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			15.0f)
	);
}
void ABasePawn::fire()
{
	/*we need to set the owner of the pawn that fired this projectile
	*so that if we need to call getOwner() of this projectile later on.. it is actually defined
	* in this project we'll need it in the onHit() callback in projectile.cpp
	*/
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
		BP_projectileClass,
		projectileSpawnPoint->GetComponentLocation(),
		projectileSpawnPoint->GetComponentRotation()
		);

	projectile->SetOwner(this);
	
}





