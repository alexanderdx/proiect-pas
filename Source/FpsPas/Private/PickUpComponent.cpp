// Copyright Epic Games, Inc. All Rights Reserved.

#include "PickUpComponent.h"


UPickUpComponent::UPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.0f;
}

void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPickUpComponent::OnSphereBeginOverlap);
}

void UPickUpComponent::OnSphereBeginOverlap(
	UPrimitiveComponent* const,
	AActor* const OtherActor,
	UPrimitiveComponent* const,
	const int32,
	const bool,
	const FHitResult&
)
{
	// Checking if it is a First Person Character overlapping
	AFpsPasCharacter* const& Character = Cast<AFpsPasCharacter>(OtherActor);
	if (!Character)
		return;

	// Notify that the actor is being picked up
	OnPickUp.Broadcast(Character);

	// Unregister from the Overlap Event so it is no longer triggered
	OnComponentBeginOverlap.RemoveAll(this);
}
