// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FpsPasCharacter.h"
#include "PickUpComponent.generated.h"


// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AFpsPasCharacter*, PickUpCharacter);

UCLASS(Abstract, Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPAS_API UPickUpComponent : public USphereComponent
{
	GENERATED_BODY()
	
	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FOnPickUp OnPickUp;

public:
	UPickUpComponent();
	
protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* const OverlappedComponent,
		AActor* const OtherActor,
		UPrimitiveComponent* const OtherComp,
		const int32 OtherBodyIndex,
		const bool bFromSweep,
		const FHitResult& SweepResult
	);
};
