// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsPasProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract, Config="Game")
class FPSPAS_API AFpsPasProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category="Projectile", meta=(AllowPrivateAccess="true"))
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AFpsPasProjectile();

protected:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* const HitComp,
		AActor* const OtherActor,
		UPrimitiveComponent* const OtherComp,
		const FVector NormalImpulse,
		const FHitResult& Hit
	);

public:
	/** Returns CollisionComp subobject **/
	FORCEINLINE USphereComponent* const& GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* const& GetProjectileMovement() const { return ProjectileMovement; }
};
