// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class AFpsPasCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPSPAS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category="Projectile", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class AFpsPasProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay", meta=(AllowPrivateAccess="true"))
	FVector MuzzleOffset;

	/** The Character holding this weapon*/
	UPROPERTY()
	AFpsPasCharacter* Character;

public:
	/** Sets default values for this component's properties */
	UWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFpsPasCharacter* const& TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

protected:
	/** Ends gameplay for this component. */
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void SpawnProjectile();
	void PlayFiringSound();
	void PlayFiringAnimation();
};
