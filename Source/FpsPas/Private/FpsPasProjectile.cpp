// Copyright Epic Games, Inc. All Rights Reserved.

#include "FpsPasProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


AFpsPasProjectile::AFpsPasProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	
	// set up a notification for when this component hits something blocking
	CollisionComp->OnComponentHit.AddDynamic(this, &AFpsPasProjectile::OnHit);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(
		FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f)
	);
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AFpsPasProjectile::OnHit(
	UPrimitiveComponent* const,
	AActor* const OtherActor,
	UPrimitiveComponent* const OtherComp,
	const FVector,
	const FHitResult&
)
{
	// Only add impulse and destroy projectile if we hit a physics
	if (!OtherActor || !OtherComp || OtherActor == this || !OtherComp->IsSimulatingPhysics())
		return;
	
	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	Destroy();
}
