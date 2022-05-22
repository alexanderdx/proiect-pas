// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimalAI.h"
#include "PreyAI.generated.h"

/**
 * 
 */
UCLASS()
class FPSPAS_API APreyAI : public AAnimalAI
{
	GENERATED_BODY()

public:
	APreyAI();
	
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnPawnHeard(APawn* InstigatorPawn, const FVector& Location, float Volume);

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class AFpsPasCharacter* TargetCharacter;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	class AHunterAI* TargetHunter;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	float RunAwayTimer = 0.f;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool bRunAway = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	bool bDead = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta=(AllowPrivateAccess = "true"))
	float WalkingSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta=(AllowPrivateAccess = "true"))
	float RunningSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta=(AllowPrivateAccess = "true"))
	float RunningAwayTimer = 6.f;

public:
	FORCEINLINE AFpsPasCharacter* GetTarget() const { return TargetCharacter; }
	FORCEINLINE bool IsRunning() const { return bRunAway; }
	FORCEINLINE bool IsDead() const { return bDead; }
};

