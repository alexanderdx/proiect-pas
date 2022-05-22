// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimalAI.h"
#include "HunterAI.generated.h"

/**
 * 
 */
UCLASS()
class FPSPAS_API AHunterAI : public AAnimalAI
{
	GENERATED_BODY()

public:
	AHunterAI();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool bChasing = false;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float FindPlayerTargetTimer = 0.f;

	UPROPERTY(EditAnywhere, Category = Movement);
	float WalkingSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta=(AllowPrivateAccess = "true"));
	float ChasingSpeed = 450.f;

	UPROPERTY(EditAnywhere, Category = Movement);
	float ChasingTimer = 6.f;
	
	/** Montage containing different attacks */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FpsPas | Combat", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;

	/** True when Enemy can attack */
	UPROPERTY(VisibleAnywhere, Category = "FpsPas | Combat", meta = (AllowPrivateAccess = "true"))
	bool bCanAttack = true;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bDead = false;

	FTimerHandle AttackWaitTimer;
	
	/** Minimum wait time between attacks */
	UPROPERTY(EditAnywhere, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float AttackWaitTime = 1.f;

	void ResetCanAttack();
	
	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage(FName Section, float PlayRate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noise", meta = (AllowPrivateAccess = "true"))
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

public:
	FORCEINLINE bool IsChasing() const { return bChasing; }
	FORCEINLINE bool IsDead() const { return bDead; }
};
