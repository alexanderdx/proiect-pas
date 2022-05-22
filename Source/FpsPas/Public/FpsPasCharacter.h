// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsPasCharacter.generated.h"


class UAnimMontage;
class UCameraComponent;
class UInputComponent;
class UNiagaraComponent;
class USceneComponent;
class USkeletalMeshComponent;
class USoundBase;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectAmmo, const int32, Ammo);

UCLASS(Abstract, Config="Game")
class FPSPAS_API AFpsPasCharacter : public ACharacter
{
	GENERATED_BODY()

	typedef struct
	{
		bool bIsPressed;
		FVector Location;
		ETouchIndex::Type FingerIndex;
		bool bMoved;
	} FTouchData;
	
	FTouchData TouchItem;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* Distorsion;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	float TurnRateGamepad;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
    int32 StonesAmountSlingshot;

	/** Delegate to whom anyone can subscribe to receive this event */
	UPROPERTY(BlueprintAssignable, Category="Interaction", meta=(AllowPrivateAccess="true"))
	FOnUseItem OnUseItem;

	UPROPERTY(BlueprintAssignable, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	FOnCollectAmmo OnCollectAmmo;

public:
	AFpsPasCharacter();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void CollectAmmo(const int32 Ammo) const;

	UFUNCTION(BlueprintCallable, Category = "Particles")
	void ToggleDistorsion() const;

protected:
	/** Fires a projectile. */
	void OnPrimaryAction();

	/** Handles moving forward/backward */
	void MoveForward(const float Value);

	/** Handles strafing movement, left and right */
	void MoveRight(const float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(const float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(const float Rate);
	
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* const PlayerInputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* const& PlayerInputComponent);
	
public:
	FORCEINLINE FTouchData& GetTouchItem() { return TouchItem; }
	FORCEINLINE const FTouchData& GetTouchItem() const { return TouchItem; }
	
	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent*& GetMesh1P() { return Mesh1P; }
	FORCEINLINE USkeletalMeshComponent* const& GetMesh1P() const { return Mesh1P; }
	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE UCameraComponent*& GetFirstPersonCameraComponent() { return FirstPersonCameraComponent; }
	FORCEINLINE UCameraComponent* const& GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	/** Returns Distorsion subobject **/
	FORCEINLINE UNiagaraComponent*& GetDistorsion() { return Distorsion; }
	FORCEINLINE UNiagaraComponent* const& GetDistorsion() const { return Distorsion; }

	FORCEINLINE const float& GetTurnRateGamepad() const { return TurnRateGamepad; }
	FORCEINLINE AFpsPasCharacter* SetTurnRateGamepad(const float& Value)
	{
		TurnRateGamepad = Value;
		return this;
	}

	FORCEINLINE const int32& GetStonesAmountSlingshot() const { return StonesAmountSlingshot; }
	FORCEINLINE AFpsPasCharacter* SetStonesAmountSlingshot(const int32& Value)
	{
		StonesAmountSlingshot = Value;
		return this;
	}

	/** Returns OnUseItem delegate **/
	FORCEINLINE FOnUseItem& GetOnUseItem() { return OnUseItem; }
	FORCEINLINE const FOnUseItem& GetOnUseItem() const { return OnUseItem; }

	/** Returns OnCollectAmmo delegate **/
	FORCEINLINE FOnCollectAmmo& GetOnStoneCollected() { return OnCollectAmmo; }
	FORCEINLINE const FOnCollectAmmo& GetOnStoneCollected() const { return OnCollectAmmo; }
};
