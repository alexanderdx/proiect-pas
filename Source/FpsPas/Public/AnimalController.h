// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AnimalController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPAS_API AAnimalController : public AAIController
{
	GENERATED_BODY()

public:
	AAnimalController();
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	/** Blackboard component for this animal */
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComponent;

	/** Behavior tree component for this animal */
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;

public:
	/** Getters */
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }
	
};
