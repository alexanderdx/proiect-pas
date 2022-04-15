// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponComponent.h"
#include "FpsPasCharacter.h"
#include "FpsPasProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UWeaponComponent::AttachWeapon(AFpsPasCharacter* const& TargetCharacter)
{
	Character = TargetCharacter;
	if (!Character)
		return;
	
	// Attach the weapon to the First Person Character
	GetOwner()->AttachToComponent(
		Character->GetMesh1P(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		FName(TEXT("GripPoint"))
	);

	// Register so that Fire is called every time the character tries to use the item being held
	Character->GetOnUseItem().AddDynamic(this, &UWeaponComponent::Fire);
}

void UWeaponComponent::Fire()
{
	if (!Character || !Character->GetController())
		return;

	SpawnProjectile();
	PlayFiringSound();
	PlayFiringAnimation();
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (!Character)
		return;
	
	// Unregister from the OnUseItem Event
	Character->GetOnUseItem().RemoveDynamic(this, &UWeaponComponent::Fire);
}

void UWeaponComponent::SpawnProjectile()
{
	// Try and fire a projectile
	if (!ProjectileClass)
		return;
	
	UWorld* const World = GetWorld();
	if (!World)
		return;
	
	const FRotator SpawnRotation = Cast<APlayerController>(
		Character->GetController()
	)->PlayerCameraManager->GetCameraRotation();
	
	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	// Spawn the projectile at the muzzle
	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	World->SpawnActor<AFpsPasProjectile>(
		ProjectileClass,
		GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset),
		SpawnRotation,
		ActorSpawnParams
	);
}

void UWeaponComponent::PlayFiringSound()
{
	// Try and play the sound if specified
	if (!FireSound)
		return;
	
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
}

void UWeaponComponent::PlayFiringAnimation()
{
	// Try and play a firing animation if specified
	if (!FireAnimation)
		return;
	
	// Get the animation object for the arms mesh
	UAnimInstance* const& AnimInstance = Character->GetMesh1P()->GetAnimInstance();
	if (!AnimInstance)
		return;
	
	AnimInstance->Montage_Play(FireAnimation, 1.0f);
}
